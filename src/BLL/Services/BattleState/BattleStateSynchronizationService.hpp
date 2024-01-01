#ifndef BATTLE_STATE_SYNCHRONIZATION_SERVICE
#define BATTLE_STATE_SYNCHRONIZATION_SERVICE

#include "vector"

#include "DAL/ApiServices/IWebSocketApiService.h"

#include "IBattleStateSynchronizationService.h"

#include "BLL/Models/Tracking/Request/FireTrackingRequest.hpp"
#include "BLL/Models/Tracking/Request/MoveTurretTrackingRequest.hpp"
#include "BLL/Models/Tracking/Request/MoveBodyTrackingRequest.hpp"

#include "Tracking/MessageHandling/IMessageHandlerFactory.h"

#include "boost/json.hpp"

namespace T10::BLL::Services::BattleState {
	class BattleStateSynchronizationService : public IBattleStateSynchronizationService {
	public:
		BattleStateSynchronizationService(
			boost::shared_ptr<DAL::ApiServices::IWebSocketApiService> socketService,
			boost::shared_ptr<Tracking::MessageHandling::IMessageHandlerFactory> messageHandlerFactory) {
			_socketService = socketService;
			_messageHandlerFactory = messageHandlerFactory;

			_socketService->setDataHandler(boost::bind(&BattleStateSynchronizationService::_onMessageReceived, this, boost::placeholders::_1));
		}

		boost::future<void> joinBattle(const std::string& battleServer) {
			return _socketService->connect(battleServer);
		}

		void leaveBattle() {
			_socketService->disconnect();
		}

		boost::future<void> moveBody(int x, int y) {
			auto model = Models::Tracking::Request::MoveBodyTrackingRequest(x, y);

			_socketService->send(model.toJson());

			boost::promise<void> p;
			return p.get_future();
		}

		void moveTurret(const irr::core::vector3df& rotation) {
			auto model = Models::Tracking::Request::MoveTurretTrackingRequest(rotation);

			_socketService->send(model.toJson());
		}

		void fire() {
			auto model = Models::Tracking::Request::FireTrackingRequest();

			_socketService->send(model.toJson());
		}
	private:
		void _onMessageReceived(const std::string& message) {
			auto parsedMessage = boost::json::parse(message);

			auto& name = parsedMessage.get_object()["name"].as_string();
			auto& value = parsedMessage.get_object()["value"].as_object();

			auto handler = _messageHandlerFactory->getHandler(name.data());

			if (handler) {
				handler->handle(value);
			}
		}

		boost::shared_ptr<DAL::ApiServices::IWebSocketApiService> _socketService;
		boost::shared_ptr<Tracking::MessageHandling::IMessageHandlerFactory> _messageHandlerFactory;
	};
}

#endif // BATTLE_STATE_SYNCHRONIZATION_SERVICE