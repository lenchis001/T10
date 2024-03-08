#ifndef MATCH_MAKING_API_SERVICE
#define MATCH_MAKING_API_SERVICE

#include "IMatchMakingApiService.h"

#include "DAL/Services/IStorageService.h"
#include "DAL/ApiServices/IWebSocketApiService.h"

#include "boost/smart_ptr.hpp"

namespace T10::DAL::ApiServices::MatchMaking {

	class MatchMakingApiService : public IMatchMakingApiService {
	public:
		MatchMakingApiService(
			boost::shared_ptr<Services::IStorageService> storageService,
			boost::shared_ptr<IWebSocketApiService> webSocketApiService
		);

		Models::ActionResult joinQueue(int tankId) override;
		void leaveQueue() override;

		void setBattleStartedHandler(OnBattleStarted handler) override;
		void setQueueLeaveHandler(OnQueueLeft handler) override;

	private:
		boost::shared_ptr<DAL::Services::IStorageService> _storageService;
		boost::shared_ptr<IWebSocketApiService> _webSocketApiService;

		OnBattleStarted _onBattleStartedHandler;
		OnQueueLeft _onQueueLeftHandler;

		void _onDataHandler(const std::string& value);
	};

}

#endif // MATCH_MAKING_API_SERVICE