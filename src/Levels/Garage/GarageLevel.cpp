#include "GarageLevel.h"

#include "boost/bind.hpp"

using namespace T10::Levels::Garage;

GarageLevel::GarageLevel(
	boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
	boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment,
	boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
	boost::shared_ptr<BLL::Services::ResourceLoading::IResourceLoadingService> resourceLoadingService,
	boost::shared_ptr<BLL::Services::User::IUserService> userService,
	boost::shared_ptr<BLL::Services::Tanks::ITankService> tankService,
	boost::shared_ptr<BLL::Services::TankAssignment::ITankAssignmentService> tankAssignemntService,
	boost::shared_ptr<StartBattleDialogController> startBattleDialogController,
	boost::shared_ptr<BuyTankDialogController> buyTankDialogController,
	SwitchLevelCallbackFunction switchLevelCallback) : BaseLevel(sceneManager, guiEnvironment, functionsProcessingAware, resourceLoadingService, switchLevelCallback),
	Mixins::LoadingSplashAwareMixin(guiEnvironment)
{
	_userService = userService;
	_tankService = tankService;
	_tankAssignmentService = tankAssignemntService;

	_startBattleDialogController = startBattleDialogController;
	_buyTankDialogController = buyTankDialogController;
}

void GarageLevel::onLoadRequested()
{
	_createUi();
	_createScene();
}

void GarageLevel::onUnloadRequested()
{

}

bool GarageLevel::OnEvent(const irr::SEvent& event)
{
	if (_startBattleDialogController->OnEvent(event)) {
		return true;
	}

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
				_showStartBattleDialog();
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

void GarageLevel::_createUi()
{
	std::wstring path = L"Resources/Levels/Garage/GUI/Garage.xml";
	_resourceLoadingService->loadGui(path);

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

void GarageLevel::_createScene()
{
	std::wstring path = L"Resources/Levels/Garage/Garage.irr";
	_resourceLoadingService->loadScene(path);

	auto target = _sceneManager->addEmptySceneNode();

	auto camera = _sceneManager->addCameraSceneNode();
	camera->addAnimator(
		boost::make_shared<T10::Levels::Cameras::GarageCameraAnimator>(target, 30));
}

void GarageLevel::_goToBattle()
{
	irr::s32 selectedTankIndex = _tanksList->getSelected();

	if (selectedTankIndex != -1)
	{
		switchToLevel(Levels::GAME, {});
	}
}

void GarageLevel::_onTankSelected()
{
	_clearGarage();

	_selectedTankIndex = _tanksList->getSelected();

	auto& tankAssignment = (*_myTanks)[_selectedTankIndex];
	auto& tank = *(std::find_if(_allTanks->begin(), _allTanks->end(), [&](auto& t) {
		return t.getId() == tankAssignment.getTankId();
		}));

	_resourceLoadingService->loadTank(tank.getName(), SELECTED_TANK_OBJECT);
}

void GarageLevel::_showStartBattleDialog()
{
	_lockGarageGui();

	_showLoadingSpalsh();

	std::wstring path = L"Resources/Levels/Garage/GUI/StartBattle.xml";
	_resourceLoadingService->loadGui(path);
	_startBattleDialogController->show(2, boost::bind(&GarageLevel::_onStartBattleDialogHidden, this));

	_hideLoadingSpalsh();
}

void GarageLevel::_showTanksBuyDialog()
{
	_lockGarageGui();

	_showLoadingSpalsh();

	std::wstring path = L"Resources/Levels/Garage/GUI/TankBuy.xml";
	_resourceLoadingService->loadGui(path);
	_buyTankDialogController->show(_allTanks, boost::bind(&GarageLevel::_onBuyTankDialogHidden, this));

	_hideLoadingSpalsh();
}

void GarageLevel::_lockGarageGui()
{
	_garageGui->setVisible(false);

	_tankService->getAll();
}

void GarageLevel::_onStartBattleDialogHidden() {
	_garageGui->setVisible(true);
}

void GarageLevel::_onBuyTankDialogHidden()
{
	_updateUserData();
	_clearGarage();
	_updatTanksList();
	_garageGui->setVisible(true);
}

bool GarageLevel::_updatTanksList() {
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

void GarageLevel::_clearGarage() {
	auto selectedTankNode = _sceneManager->getSceneNodeFromId(SELECTED_TANK_OBJECT);

	if (selectedTankNode) {
		selectedTankNode->remove();
	}
}

bool GarageLevel::_updateUserData() {
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