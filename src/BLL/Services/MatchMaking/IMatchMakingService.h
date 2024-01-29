#ifndef IMATCH_MAKING_SERVICE
#define IMATCH_MAKING_SERVICE

#include "BLL/Models/ActionResult.h"

namespace T10::BLL::Services::BattleState {

	class IMatchMakingService {
	public:
		ActionResult joinQueue(int tankId);
	};

}

#endif // IMATCH_MAKING_SERVICE