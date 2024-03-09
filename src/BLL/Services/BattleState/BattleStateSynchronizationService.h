#ifndef BATTLE_STATE_SYNCHRONIZATION_SERVICE_H
#define BATTLE_STATE_SYNCHRONIZATION_SERVICE_H

#include "IBattleStateSynchronizationService.h"

#include "vector"

#include "boost/json.hpp"

#include "DAL/ApiServices/IWebSocketApiService.h"

#include "BLL/Models/Tracking/Request/FireTrackingRequest.hpp"
#include "BLL/Models/Tracking/Request/MoveTurretTrackingRequest.hpp"
#include "BLL/Models/Tracking/Request/MoveBodyTrackingRequest.hpp"

#include "Tracking/MessageHandling/IMessageHandlerFactory.h"

namespace T10::BLL::Services::BattleState {
	class BattleStateSynchronizationService : public IBattleStateSynchronizationService {
	public:
		BattleStateSynchronizationService(
			boost::shared_ptr<DAL::ApiServices::IWebSocketApiService> socketService,
			boost::shared_ptr<Tracking::MessageHandling::IMessageHandlerFactory> messageHandlerFactory);

		boost::future<void> joinBattle(const std::string& battleServer, const std::string& apiKey) override;
		void leaveBattle() override;
		bool OnEvent(const irr::SEvent::SKeyInput& eventData) override;

	private:
		void _onMessageReceived(const std::string& message);
		boost::future<void> _moveBody(int x, int y);
		void _reportMoveX();
		void _reportMoveY();
		void _moveTurret(const irr::core::vector3df& rotation);
		void _fire();

		int _moveX, _moveY, _lastReportedMoveX, _lastReportedMoveY;
		boost::shared_ptr<DAL::ApiServices::IWebSocketApiService> _socketService;
		boost::shared_ptr<Tracking::MessageHandling::IMessageHandlerFactory> _messageHandlerFactory;
	};
}

#endif // BATTLE_STATE_SYNCHRONIZATION_SERVICE_H