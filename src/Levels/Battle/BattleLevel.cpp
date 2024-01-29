#include "BattleLevel.h"

using namespace T10::Levels::Battle;

BattleLevel::BattleLevel(
	boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
	boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment,
	boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
	boost::shared_ptr<BLL::Services::ResourceLoading::IResourceLoadingService> resourceLoadingService,
	boost::shared_ptr<irr::gui::ICursorControl> cursorControl,
	boost::shared_ptr<BLL::Services::BattleState::IBattleStateSynchronizationService> battleStateSynchronizationService,
	SwitchLevelCallbackFunction switchLevelCallback)
	: BaseLevel(sceneManager, guiEnvironment, functionsProcessingAware, resourceLoadingService, switchLevelCallback),
	Mixins::LoadingSplashAwareMixin(guiEnvironment)
{
	_cursorControl = cursorControl;
	_battleStateSynchronizationService = battleStateSynchronizationService;
}

void BattleLevel::onLoadRequested()
{
	_createUi();
	_createScene();

	_battleStateSynchronizationService->joinBattle("ws://localhost:8080", "33e9e476-69c9-4bc3-9eb5-3ff0de6cebee");
}

void BattleLevel::onUnloadRequested()
{
	// Implementation here ...
}

bool BattleLevel::OnEvent(const irr::SEvent& event)
{
	if (event.EventType == irr::EEVENT_TYPE::EET_GUI_EVENT)
	{
		switch (event.GUIEvent.EventType)
		{
		case irr::gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED:
		{
			boost::shared_ptr<irr::gui::IGUIButton> button = boost::static_pointer_cast<irr::gui::IGUIButton>(event.GUIEvent.Caller);

			switch (event.GUIEvent.Caller->getID())
			{

			default:
				break;
			}

			break;
		}
		default:
			break;
		}
	}
	else if (event.EventType == irr::EEVENT_TYPE::EET_KEY_INPUT_EVENT && _battleStateSynchronizationService->OnEvent(event.KeyInput))
	{
		return true;
	}

	return BaseLevel::OnEvent(event);
}

void BattleLevel::_createUi()
{
	std::wstring path = L"Resources/GUI/Battle/Status.xml";
	_resourceLoadingService->loadGui(path);

	path = L"Resources/GUI/Battle/Aim.xml";
	_resourceLoadingService->loadGui(path);

	_centerAim();
}

void BattleLevel::_createScene()
{
	// Implementation here ...
}

void BattleLevel::_centerAim()
{
	auto aim = _guiEnvironment->getRootGUIElement()->getElementFromId(AIM_CONTROL);

	auto parentRect = aim->getParent()->getAbsoluteClippingRect().getSize();
	auto rect = aim->getAbsolutePosition().getSize();

	aim->setRelativePosition(parentRect / 2 - rect / 2);
}