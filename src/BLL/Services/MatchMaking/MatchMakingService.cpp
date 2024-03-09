#include "MatchMakingService.h"

#include "boost/bind.hpp"

#include "Utils/Utils.h"

using namespace T10;
using namespace T10::BLL::Models;
using namespace T10::BLL::Services::MatchMaking;

MatchMakingService::MatchMakingService(
	boost::shared_ptr<DAL::ApiServices::MatchMaking::IMatchMakingApiService> matchMakingApiService,
	boost::shared_ptr<DAL::Services::IStorageService> storageService) {
	_matchMakingApiService = matchMakingApiService;
	_storageService = storageService;
}

BLL::Models::DataActionResult<boost::future<void>> MatchMakingService::joinQueue(int tankId) {
	auto dalResult = _matchMakingApiService->joinQueue(tankId);

	auto error = _toBllError(dalResult.getError());

	return DataActionResult<boost::future<void>>(error, dalResult.getData());
}

void MatchMakingService::leaveQueue() {
	_matchMakingApiService->leaveQueue();
}

void MatchMakingService::setBattleStartedHandler(OnBattleStarted handler) {
	//_matchMakingApiService->setBattleStartedHandler(handler);
}

void MatchMakingService::setQueueLeftHandler(OnQueueLeft handler) {
	_matchMakingApiService->setQueueLeaveHandler(handler);
}