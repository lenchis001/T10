#ifndef IMATCH_MAKING_API_SERVICE
#define IMATCH_MAKING_API_SERVICE

#include "boost/function.hpp"
#include "DAL/Models/ActionResult.h"

#include "DAL/Models/MatchMaking/Response/StartBattleMessage.hpp"

namespace T10::DAL::ApiServices::MatchMaking {

	typedef boost::function<void(const DAL::Models::MatchMaking::Response::StartBattleMessage&)> OnBattleStarted;
	typedef boost::function<void()> OnQueueLeft;

	class IMatchMakingApiService {
	public:
		virtual Models::ActionResult joinQueue(int tankId) = 0;
		virtual void leaveQueue() = 0;

		virtual void setBattleStartedHandler(OnBattleStarted handler) = 0;
		virtual void setQueueLeaveHandler(OnQueueLeft handler) = 0;
	};

}


#endif // IMATCH_MAKING_API_SERVICE