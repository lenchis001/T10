#include "GarageLevel.h"

namespace GameLogic {
	GarageLevel::GarageLevel(boost::shared_ptr<irr::scene::ISceneManager> sceneManager, boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment, SwitchLevelCallbackFunction switchLevelCallback) :
		BaseLevel(sceneManager, guiEnvironment, switchLevelCallback)
	{
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
		if (event.EventType == irr::EEVENT_TYPE::EET_GUI_EVENT) {
			if (event.GUIEvent.EventType == irr::gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED)
				return true;
		}

		return false;
	}

	void GarageLevel::_createUi()
	{
		std::wstring path = L"Resources/GUI/HUD.xml";
		_loadGui(path);
	}

	void GarageLevel::_createScene()
	{
		std::wstring path = L"Resources/Levels/Garage/Garage.irr";

		_loadScene(path);
		_sceneManager->addCameraSceneNodeMaya();
	}

	void GarageLevel::_goToBattle(irr::gui::IGUIButton* button)
	{
	}
}