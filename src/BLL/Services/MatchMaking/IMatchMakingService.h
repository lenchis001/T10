#ifndef IMATCH_MAKING_SERVICE
#define IMATCH_MAKING_SERVICE

#include "BLL/Models/ActionResult.h"

#include "boost/function.hpp"

namespace T10::BLL::Services::MatchMaking {

	typedef boost::function<void()> OnBattleStarted;
	typedef boost::function<void()> OnQueueLeft;

	class IMatchMakingService {
	public:
		virtual Models::ActionResult joinQueue(int tankId) = 0;
		virtual void leaveQueue() = 0;

		virtual void setBattleStartedHandler(OnBattleStarted handler) = 0;
		virtual void setQueueLeftHandler(OnQueueLeft handler) = 0;
	};

}

#endif // IMATCH_MAKING_SERVICE