#ifndef START_BATTLE_DIALOG_CONTROLLER
#define START_BATTLE_DIALOG_CONTROLLER

#include "IFunctionsProcessingAware.h"
#include "BLL/Services/MatchMaking/IMatchMakingService.h"

#include "irrlicht.h"

#include "vector"

#include "boost/function.hpp"
#include "boost/smart_ptr.hpp"

#define START_BATTLE_DIALOG_CONTROL 20

namespace T10::Levels::Garage
{
	class StartBattleDialogController
	{
	public:
		StartBattleDialogController(
			boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
			boost::shared_ptr<BLL::Services::MatchMaking::IMatchMakingService> matchMakingService,
			boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment);

		void show(int tankId, boost::function<void()> onHidden);
		bool OnEvent(const irr::SEvent& event);

	private:
		boost::shared_ptr<IFunctionsProcessingAware> _functionsProcessingAware;
		boost::shared_ptr<irr::gui::IGUIEnvironment> _guiEnvironment;
		boost::shared_ptr<BLL::Services::MatchMaking::IMatchMakingService> _matchMakingService;

		boost::function<void()> _onHidden;

		void _onBattleStarted();
		void _onBattleLeft();
	};
}

#endif // START_BATTLE_DIALOG_CONTROLLER