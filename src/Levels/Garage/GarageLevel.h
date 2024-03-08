#ifndef GARAGE_LEVEL_H
#define GARAGE_LEVEL_H

#include "iostream"
#include "future"

#include "boost/smart_ptr.hpp"
#include "boost/function.hpp"

#include "Levels/BaseLevel.h"

#include "Levels/Mixins/LoadingSplashAwareMixin.h"

#include "BLL/Services/User/IUserService.h"
#include "BLL/Services/Tank/ITankService.h"
#include "BLL/Services/TankAssignment/ITankAssignmentService.h"

#include "Levels/Cameras/GarageCameraAnimator.h"

#include "Levels/Garage/BuyTankDialogController.h"
#include "Levels/Garage/StartBattleDialogController.h"

namespace T10::Levels::Garage
{
#define SELECTED_TANK_OBJECT 1001

#define TANKS_LIST_CONTROL 1
#define GO_TO_BATTLE_CONTROL 2
#define USER_NAME_CONTROL 3
#define MONEY_VALUE_CONTROL 4
#define BUY_TANK_CONTROL 5
#define GARAGE_UI 7

	class GarageLevel : public BaseLevel, public Mixins::LoadingSplashAwareMixin, public boost::enable_shared_from_this<ILevel>
	{
	public:
		GarageLevel(
			boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
			boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment,
			boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
			boost::shared_ptr<BLL::Services::ResourceLoading::IResourceLoadingService> resourceLoadingService,
			boost::shared_ptr<BLL::Services::User::IUserService> userService,
			boost::shared_ptr<BLL::Services::Tanks::ITankService> tankService,
			boost::shared_ptr<BLL::Services::TankAssignment::ITankAssignmentService> tankAssignemntService,
			boost::shared_ptr<StartBattleDialogController> startBattleDialogController,
			boost::shared_ptr<BuyTankDialogController> buyTankDialogController,
			SwitchLevelCallbackFunction switchLevelCallback);

		void onLoadRequested() override;
		void onUnloadRequested() override;
		bool OnEvent(const irr::SEvent& event) override;

	private:
		void _createUi();
		void _createScene();
		void _goToBattle();
		void _onTankSelected();
		void _showStartBattleDialog();
		void _showTanksBuyDialog();
		void _lockGarageGui();
		void _onBuyTankDialogHidden();
		void _onStartBattleDialogHidden();
		bool _updatTanksList();
		void _clearGarage();
		bool _updateUserData();

		boost::shared_ptr<irr::gui::IGUIElement> _garageGui;
		boost::shared_ptr<irr::gui::IGUIListBox> _tanksList;
		boost::shared_ptr<const std::vector<BLL::Models::Tanks::Tank>> _allTanks;
		boost::shared_ptr<std::vector<BLL::Models::TankAssignments::TankAssignment>> _myTanks;
		int _selectedTankIndex = -1;

		boost::shared_ptr<BLL::Services::User::IUserService> _userService;
		boost::shared_ptr<BLL::Services::Tanks::ITankService> _tankService;
		boost::shared_ptr<BLL::Services::TankAssignment::ITankAssignmentService> _tankAssignmentService;

		boost::shared_ptr<BuyTankDialogController> _buyTankDialogController;
		boost::shared_ptr< StartBattleDialogController> _startBattleDialogController;
	};
}

#endif // GARAGE_LEVEL_H