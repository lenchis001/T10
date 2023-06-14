#include "GarageLevel.h"
#include "cameras/GarageCameraAnimator.h"
#include "iostream"

namespace T10
{
#define TANKS_LIST_CONTROL 1
#define GO_TO_BATTLE_CONTROL 2

	GarageLevel::GarageLevel(
		boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
		boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment,
		boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
		boost::shared_ptr<bll::services::User::IUserService> userService,
		SwitchLevelCallbackFunction switchLevelCallback)
		: BaseLevel(sceneManager, guiEnvironment, functionsProcessingAware, switchLevelCallback)
	{
		_userService = userService;
	}

	void GarageLevel::onLoadRequested()
	{
		_createUi();
		_createScene();
	}

	void GarageLevel::onUnloadRequested()
	{
	}

	bool GarageLevel::OnEvent(const irr::SEvent &event)
	{
		if (event.EventType == irr::EEVENT_TYPE::EET_GUI_EVENT)
		{
			if (event.GUIEvent.EventType == irr::gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED)
			{
				boost::shared_ptr<irr::gui::IGUIButton> button = boost::static_pointer_cast<irr::gui::IGUIButton>(event.GUIEvent.Caller);
				if (button->getID() == GO_TO_BATTLE_CONTROL)
				{
					_goToBattle();
				}

				return true;
			}
		}

		return false;
	}

	void GarageLevel::_createUi()
	{
		std::wstring path = L"Resources/Levels/Garage/GUI/Garage.xml";
		_loadGui(path);

		_functionsProcessingAware->addFuctionToQueue(
			ThreadTypes::THREAD_POOL,
			[&]()
			{
				boost::shared_ptr<bll::models::ActionResult<bll::models::user::Info>> userInfo = _userService->getInfo();
				
				_functionsProcessingAware->addFuctionToQueue(ThreadTypes::RENDER_THREAD, [&, userInfo]() {
					boost::shared_ptr<irr::gui::IGUIElement> element = _guiEnvironment->getRootGUIElement()->getElementFromId(TANKS_LIST_CONTROL, true);
					_tanksList = boost::static_pointer_cast<irr::gui::IGUIListBox>(element);

					_tanksList->addItem(userInfo->getData().getName().c_str());
				
				}); 
			});
	}

	void GarageLevel::_createScene()
	{
		std::wstring path = L"Resources/Levels/Garage/Garage.irr";
		_loadScene(path);

		_sceneManager->addCameraSceneNode()->addAnimator(
			boost::make_shared<T10::levels::garage::cameras::GarageCameraAnimator>(irr::core::vector3df(0, 2, 0), 10));
	}

	void GarageLevel::_goToBattle()
	{
		irr::s32 selectedTankIndex = _tanksList->getSelected();

		if (selectedTankIndex != -1)
		{
		}
	}
}