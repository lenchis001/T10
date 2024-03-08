#ifndef MATCH_MAKING_SERVICE
#define MATCH_MAKING_SERVICE

#include "IMatchMakingService.h"
#include "DAL/ApiServices/MatchMaking/IMatchMakingApiService.h"
#include "DAL/Services/IStorageService.h"

#include "BLL/Services/BaseService.h"

#include "string"

#include "boost/smart_ptr.hpp"

namespace T10::BLL::Services::MatchMaking {

	class MatchMakingService : public BaseService, public IMatchMakingService {
	public:
		MatchMakingService(
			boost::shared_ptr<DAL::ApiServices::MatchMaking::IMatchMakingApiService> matchMakingApiService,
			boost::shared_ptr<DAL::Services::IStorageService> storageService
		);

		Models::ActionResult joinQueue(int tankId) override;
		void leaveQueue() override;

		void setBattleStartedHandler(OnBattleStarted handler) override;
		void setQueueLeftHandler(OnQueueLeft handler) override;
	private:
		boost::shared_ptr<DAL::ApiServices::MatchMaking::IMatchMakingApiService> _matchMakingApiService;
		boost::shared_ptr<DAL::Services::IStorageService> _storageService;
	};

}

#endif // MATCH_MAKING_SERVICE