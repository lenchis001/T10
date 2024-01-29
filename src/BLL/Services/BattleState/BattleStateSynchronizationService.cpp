#include "BattleStateSynchronizationService.h"

using namespace T10::BLL::Services::BattleState;

BattleStateSynchronizationService::BattleStateSynchronizationService(
	boost::shared_ptr<DAL::ApiServices::IWebSocketApiService> socketService,
	boost::shared_ptr<Tracking::MessageHandling::IMessageHandlerFactory> messageHandlerFactory) {
	_socketService = socketService;
	_messageHandlerFactory = messageHandlerFactory;
	_socketService->setDataHandler(boost::bind(&BattleStateSynchronizationService::_onMessageReceived, this, boost::placeholders::_1));
	_moveX = _moveY = _lastReportedMoveX = _lastReportedMoveY = 0;
}

boost::future<void> BattleStateSynchronizationService::joinBattle(const std::string& battleServer, const std::string& apiKey) {
	return _socketService->connect(battleServer, apiKey);
}

void BattleStateSynchronizationService::leaveBattle() {
	_socketService->disconnect();
}

bool BattleStateSynchronizationService::OnEvent(const irr::SEvent::SKeyInput& eventData) {
	switch (eventData.Key)
	{
	case irr::EKEY_CODE::KEY_KEY_W:
		_moveX = eventData.PressedDown;
		_reportMoveX();
		return true;
	case irr::EKEY_CODE::KEY_KEY_S:
		_moveX = -eventData.PressedDown;
		_reportMoveX();
		return true;
	case irr::EKEY_CODE::KEY_KEY_A:
		_moveY = -eventData.PressedDown;
		_reportMoveY();
		return true;
	case irr::EKEY_CODE::KEY_KEY_D:
		_moveY = eventData.PressedDown;
		_reportMoveY();
		return true;
	default:
		break;
	}
	return false;
}

void BattleStateSynchronizationService::_onMessageReceived(const std::string& message) {
	auto parsedMessage = boost::json::parse(message);
	auto& name = parsedMessage.get_object()["name"].as_string();
	auto& value = parsedMessage.get_object()["value"].as_object();
	auto handler = _messageHandlerFactory->getHandler(name.data());

	if (handler) {
		handler->handle(value);
	}
}

boost::future<void> BattleStateSynchronizationService::_moveBody(int x, int y) {
	auto model = Models::Tracking::Request::MoveBodyTrackingRequest(x, y);

	_socketService->send(model.toJson());

	boost::promise<void> p;
	return p.get_future();
}

void BattleStateSynchronizationService::_reportMoveX() {
	if (_lastReportedMoveX != _moveX) {
		_moveBody(_moveX, _moveY);
		_lastReportedMoveX = _moveX;
	}
}

void BattleStateSynchronizationService::_reportMoveY() {
	if (_lastReportedMoveY != _moveY) {
		_moveBody(_moveX, _moveY);
		_lastReportedMoveY = _moveY;
	}
}

void BattleStateSynchronizationService::_moveTurret(const irr::core::vector3df& rotation) {
	auto model = Models::Tracking::Request::MoveTurretTrackingRequest(rotation);

	_socketService->send(model.toJson());
}

void BattleStateSynchronizationService::_fire() {
	auto model = Models::Tracking::Request::FireTrackingRequest();

	_socketService->send(model.toJson());
}