#ifndef IBATTLE_STATE_SYNCHRONIZATION_SERVICE
#define IBATTLE_STATE_SYNCHRONIZATION_SERVICE

#include "irrlicht.h"

#define BOOST_THREAD_PROVIDES_FUTURE
#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION

#include <boost/thread/future.hpp>

namespace T10::BLL::Services::BattleState {
	class IBattleStateSynchronizationService {
	public:
		virtual boost::future<void> joinBattle(const std::string& battleServer, const std::string& apiKey) = 0;
		virtual void leaveBattle() = 0;

		virtual bool OnEvent(const irr::SEvent::SKeyInput& eventData) = 0;
	};
}

#endif // IBATTLE_STATE_SYNCHRONIZATION_SERVICE