#ifndef IBATTLE_STATE_SYNCHRONIZATION_SERVICE
#define IBATTLE_STATE_SYNCHRONIZATION_SERVICE

#include "irrlicht.h"

#define BOOST_THREAD_PROVIDES_FUTURE
#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION

#include <boost/thread/future.hpp>

#include "Tracking/ITrackableObject.h"
#include "Tracking/ITrackableTank.h"

namespace T10::BLL::Services::BattleState {
	class IBattleStateSynchronizationService {
	public:
		virtual boost::future<void> joinBattle(const std::string& battleServer) = 0;
		virtual void leaveBattle() = 0;

		virtual boost::future<void> moveBody(int left, int right) = 0;
		virtual boost::future<void> moveTurret(const irr::core::vector3df& target) = 0;

		virtual void fire() = 0;

		virtual void addTrackableObject(boost::shared_ptr<Tracking::ITrackableObject> object) = 0;
		virtual void addTrackableTank(boost::shared_ptr<Tracking::ITrackableTank> tank) = 0;
	};
}

#endif // IBATTLE_STATE_SYNCHRONIZATION_SERVICE