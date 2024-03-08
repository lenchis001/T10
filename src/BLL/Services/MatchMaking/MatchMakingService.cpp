#include "MatchMakingService.h"

#include "boost/bind.hpp"

#include "Utils/Utils.h"

using namespace T10;
using namespace T10::BLL::Models;
using namespace T10::BLL::Services::MatchMaking;

MatchMakingService::MatchMakingService(
	boost::shared_ptr<DAL::ApiServices::MatchMaking::IMatchMakingApiService> matchMakingApiService,
	boost::shared_ptr<DAL::Services::IStorageService> storageService) {
	_matchMakingApiService = matchMakingApiService;
	_storageService = storageService;
}

ActionResult MatchMakingService::joinQueue(int tankId) {
	auto dalResult = _matchMakingApiService->joinQueue(tankId);

	return _toBllActionResult(dalResult);
}

void MatchMakingService::leaveQueue() {
	_matchMakingApiService->leaveQueue();
}

void MatchMakingService::setBattleStartedHandler(OnBattleStarted handler) {
	//_matchMakingApiService->setBattleStartedHandler(handler);
}

void MatchMakingService::setQueueLeftHandler(OnQueueLeft handler) {
	_matchMakingApiService->setQueueLeaveHandler(handler);
}