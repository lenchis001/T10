#ifndef BATTLE_STATE_SYNCHRONIZATION_SERVICE
#define BATTLE_STATE_SYNCHRONIZATION_SERVICE

#include "vector"

#include "DAL/ApiServices/IWebSocketApiService.h"

#include "IBattleStateSynchronizationService.h"

#include "BLL/Models/Tracking/Request/FireTrackingRequest.hpp"

namespace T10::BLL::Services::BattleState {
	class BattleStateSynchronizationService : public IBattleStateSynchronizationService {
	public:
		BattleStateSynchronizationService(boost::shared_ptr<DAL::ApiServices::IWebSocketApiService> socketService) {
			_socketService = socketService;
		}

		boost::future<void> joinBattle(const std::string& battleServer) {
			return _socketService->connect(battleServer);
		}

		void leaveBattle() {
			_trackableObjects.clear();
			_trackableTanks.clear();

			_socketService->disconnect();
		}

		boost::future<void> moveBody(int left, int right) {
			throw "";
		}

		boost::future<void> moveTurret(const irr::core::vector3df& target) {
			throw "";
		}

		void fire() {
			auto fireRequest = Models::Tracking::Request::FireTrackingRequest();

			_socketService->send(fireRequest.toJson());
		}

		void addTrackableObject(boost::shared_ptr<Tracking::ITrackableObject> object) {
			_trackableObjects.push_back(object);
		}

		void addTrackableTank(boost::shared_ptr<Tracking::ITrackableTank> tank) {
			_trackableTanks.push_back(tank);
		}

	private:
		boost::shared_ptr<DAL::ApiServices::IWebSocketApiService> _socketService;

		std::vector<boost::shared_ptr<Tracking::ITrackableObject>> _trackableObjects;
		std::vector<boost::shared_ptr<Tracking::ITrackableTank>> _trackableTanks;
	};
}

#endif // BATTLE_STATE_SYNCHRONIZATION_SERVICE