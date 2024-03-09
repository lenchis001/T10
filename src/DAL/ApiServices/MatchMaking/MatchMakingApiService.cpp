#include "MatchMakingApiService.h"

#include "map"

#include "Utils/Utils.h"

#include "boost/json.hpp"

#include "DAL/Models/MatchMaking/Request/LeaveQueueMessage.hpp"

using namespace T10::DAL::Models;
using namespace T10::DAL::Models::MatchMaking::Response;
using namespace T10::DAL::ApiServices::MatchMaking;

MatchMakingApiService::MatchMakingApiService(
	boost::shared_ptr<DAL::Services::IStorageService> storageService,
	boost::shared_ptr<IWebSocketApiService> webSocketApiService) {
	_storageService = storageService;
	_webSocketApiService = webSocketApiService;

	_webSocketApiService->setDataHandler(boost::bind(&MatchMakingApiService::_onDataHandler, this, boost::placeholders::_1));
}

ActionResult MatchMakingApiService::joinQueue(int tankId) {
	auto token = _storageService->get(TOKEN_STORAGE_KEY);

	std::map<std::string, std::string> headers;
	headers["Authorization"] = "Bearer " + TO_STRING(token);
	headers["tankid"] = std::to_string(tankId);

	_webSocketApiService->connect("ws://localhost:8086", headers).;

	return ActionResult::okResult();
}

void MatchMakingApiService::leaveQueue() {
	auto message = Models::MatchMaking::Request::LeaveQueueMessage();

	_webSocketApiService->send(boost::json::serialize(message.toJson()));
}

void MatchMakingApiService::setBattleStartedHandler(OnBattleStarted handler) {
	_onBattleStartedHandler = handler;
}

void MatchMakingApiService::setQueueLeaveHandler(OnQueueLeft handler) {
	_onQueueLeftHandler = handler;
}

void MatchMakingApiService::_onDataHandler(const std::string& message) {
	auto parsedMessage = boost::json::parse(message);

	const auto& name = parsedMessage.at("name").as_string();
	const auto& value = parsedMessage.at("name").as_object();

	if (name == "queueLeft") {
		_onQueueLeftHandler();
	}
	else if (name == "battleStarted") {
		auto startBattleMessage = StartBattleMessage::fromJson(value);

		_onBattleStartedHandler(startBattleMessage);
	}
	else {
		// todo: log it
	}
}