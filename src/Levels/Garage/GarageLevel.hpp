#ifndef GARAGE_LEVEL
#define GARAGE_LEVEL

#include "iostream"

#include "boost/smart_ptr.hpp"
#include "boost/function.hpp"

#include "Levels/BaseLevel.hpp"

#include "Levels/Mixins/LoadingSplashAwareMixing.hpp"

#include "BLL/Services/User/IUserService.h"
#include "BLL/Services/Tank/ITankService.h"
#include "BLL/Services/TankAssignment/ITankAssignmentService.h"

#include "Cameras/GarageCameraAnimator.hpp"

#include "Levels/Garage/BuyTankDialogController.hpp"

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
			boost::shared_ptr<BLL::Services::User::IUserService> userService,
			boost::shared_ptr<BLL::Services::Tanks::ITankService> tankService,
			boost::shared_ptr<BLL::Services::TankAssignment::ITankAssignmentService> tankAssignemntService,
			boost::shared_ptr<BuyTankDialogController> buyTankDialogController,
			SwitchLevelCallbackFunction switchLevelCallback) : BaseLevel(sceneManager, guiEnvironment, functionsProcessingAware, switchLevelCallback),
			Mixins::LoadingSplashAwareMixin(guiEnvironment)
		{
			_userService = userService;
			_tankService = tankService;
			_tankAssignmentService = tankAssignemntService;

			_buyTankDialogController = buyTankDialogController;
		}

		void onLoadRequested() override
		{
			_createUi();
			_createScene();
		}

		void onUnloadRequested() override
		{
		}

		bool OnEvent(const irr::SEvent& event) override
		{
			if (_buyTankDialogController->OnEvent(event)) {
				return true;
			}

			if (event.EventType == irr::EEVENT_TYPE::EET_GUI_EVENT)
			{
				switch (event.GUIEvent.EventType)
				{
				case irr::gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED:
				{
					boost::shared_ptr<irr::gui::IGUIButton> button = boost::static_pointer_cast<irr::gui::IGUIButton>(event.GUIEvent.Caller);

					switch (event.GUIEvent.Caller->getID())
					{
					case GO_TO_BATTLE_CONTROL:
						_goToBattle();
						return true;

					case BUY_TANK_CONTROL:
						_showTanksBuyDialog();
						return true;

					default:
						break;
					}

					break;
				}
				case irr::gui::EGUI_EVENT_TYPE::EGET_LISTBOX_CHANGED:
				{
					if (event.GUIEvent.Caller->getID() == TANKS_LIST_CONTROL)
					{
						_onTankSelected();
						return true;
					}

					break;
				}
				default:
					break;
				}
			}

			return BaseLevel::OnEvent(event);
		}

	private:
		boost::shared_ptr<irr::gui::IGUIElement> _garageGui;
		boost::shared_ptr<irr::gui::IGUIListBox> _tanksList;
		boost::shared_ptr<const std::vector<BLL::Models::Tanks::Tank>> _allTanks;
		boost::shared_ptr<std::vector<BLL::Models::TankAssignments::TankAssignment>> _myTanks;
		int _selectedTankIndex = -1;

		boost::shared_ptr<BLL::Services::User::IUserService> _userService;
		boost::shared_ptr<BLL::Services::Tanks::ITankService> _tankService;
		boost::shared_ptr<BLL::Services::TankAssignment::ITankAssignmentService> _tankAssignmentService;

		boost::shared_ptr<BuyTankDialogController> _buyTankDialogController;

		void _createUi()
		{
			std::wstring path = L"Resources/Levels/Garage/GUI/Garage.xml";
			_loadGui(path);

			auto rootGuiElement = _guiEnvironment->getRootGUIElement();
			_garageGui = rootGuiElement->getElementFromId(GARAGE_UI);

			boost::shared_ptr<irr::gui::IGUIElement> element = rootGuiElement->getElementFromId(TANKS_LIST_CONTROL, true);
			_tanksList = boost::static_pointer_cast<irr::gui::IGUIListBox>(element);

			_showLoadingSpalsh();

			if (!_updateUserData()) {
				return;
			}

			if (!_updatTanksList()) {
				return;
			}

			_hideLoadingSpalsh();
		}

		void _createScene()
		{
			std::wstring path = L"Resources/Levels/Garage/Garage.irr";
			_loadScene(path);

			_sceneManager->addCameraSceneNode()->addAnimator(
				boost::make_shared<T10::Levels::Garage::Cameras::GarageCameraAnimator>(irr::core::vector3df(0, 0, 0), 10));
		}

		void _goToBattle()
		{
			irr::s32 selectedTankIndex = _tanksList->getSelected();

			if (selectedTankIndex != -1)
			{
				switchToLevel(Levels::GAME, {});
			}
		}

		void _onTankSelected()
		{
			_clearGarage();

			_selectedTankIndex = _tanksList->getSelected();

			auto& tank = (*_allTanks)[_selectedTankIndex];

			auto modelPath = std::wstring(L"Resources/Models/Tanks/") + tank.getName() + std::wstring(L"/Tank.obj");

			auto mesh = _sceneManager->getMesh(modelPath.c_str());
			_sceneManager->addMeshSceneNode(mesh)->setID(SELECTED_TANK_OBJECT);
		}

		void _showTanksBuyDialog()
		{
			_lockGarageGui();

			_showLoadingSpalsh();

			std::wstring path = L"Resources/Levels/Garage/GUI/TankBuy.xml";
			_loadGui(path);
			_buyTankDialogController->show(_allTanks, boost::bind(&GarageLevel::_onBuyTankDialogHidden, this));

			_hideLoadingSpalsh();
		}

		void _lockGarageGui()
		{
			_garageGui->setVisible(false);

			_tankService->getAll();
		}

		void _onBuyTankDialogHidden()
		{
			_updateUserData();
			_clearGarage();
			_updatTanksList();
			_garageGui->setVisible(true);
		}

		bool _updatTanksList() {
			boost::shared_ptr<BLL::Models::DataActionResult<std::vector<BLL::Models::Tanks::Tank>>> allTank = _tankService->getAll();
			if (!allTank->isOk())
			{
				std::wstring message(L"Cannot get tanks info.");

				_exitWithMessage(message);
				return false;
			}
			_allTanks = boost::make_shared<const std::vector<BLL::Models::Tanks::Tank>>(allTank->getData());

			boost::shared_ptr<BLL::Models::DataActionResult<std::vector<BLL::Models::TankAssignments::TankAssignment>>> myTanks = _tankAssignmentService->getMy();
			if (!myTanks->isOk())
			{
				std::wstring message(L"Cannot get user's tanks info.");

				_exitWithMessage(message);
				return false;
			}
			_myTanks = boost::make_shared<std::vector<BLL::Models::TankAssignments::TankAssignment>>(myTanks->getData());

			_tanksList->clear();

			for (const BLL::Models::Tanks::Tank& tank : *_allTanks)
			{
				if (std::find_if(_myTanks->begin(), _myTanks->end(), [&](auto t)
					{ return t.getTankId() == tank.getId(); }) != _myTanks->end())
				{
					_tanksList->addItem(tank.getName().c_str());
				}
			}

			return true;
		}

		void _clearGarage() {
			auto selectedTankNode = _sceneManager->getSceneNodeFromId(SELECTED_TANK_OBJECT);

			if (selectedTankNode) {
				selectedTankNode->remove();
			}
		}

		bool _updateUserData() {
			boost::shared_ptr<BLL::Models::DataActionResult<BLL::Models::User::Info>> userInfo = _userService->getInfo();
			if (!userInfo->isOk())
			{
				std::wstring message(L"Cannot get user info.");

				_exitWithMessage(message);
				return false;
			}

			auto rootGuiElement = _guiEnvironment->getRootGUIElement();

			boost::shared_ptr<irr::gui::IGUIElement> element;

			element = rootGuiElement->getElementFromId(USER_NAME_CONTROL, true);
			boost::shared_ptr<irr::gui::IGUIStaticText> userNameLabel = boost::static_pointer_cast<irr::gui::IGUIStaticText>(element);
			userNameLabel->setText(userInfo->getData().getName().c_str());

			element = rootGuiElement->getElementFromId(MONEY_VALUE_CONTROL, true);
			boost::shared_ptr<irr::gui::IGUIStaticText> moneyLabel = boost::static_pointer_cast<irr::gui::IGUIStaticText>(element);
			moneyLabel->setText(std::to_wstring(userInfo->getData().getMoney()).c_str());

			return true;
		}
	};
}

#endif