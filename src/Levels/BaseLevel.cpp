#include "BaseLevel.h"

namespace T10::Levels
{
	BaseLevel::BaseLevel(
		boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
		boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment,
		boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
		boost::shared_ptr<BLL::Services::ResourceLoading::IResourceLoadingService> resourceLoadingService,
		SwitchLevelCallbackFunction switchLevelCallback) : _sceneManager(sceneManager),
		_guiEnvironment(guiEnvironment),
		_functionsProcessingAware(functionsProcessingAware),
		_resourceLoadingService(resourceLoadingService),
		_switchLevelCallback(switchLevelCallback)
	{}

	void BaseLevel::load() {}

	bool BaseLevel::OnEvent(const irr::SEvent& event)
	{
		if (event.EventType == irr::EEVENT_TYPE::EET_GUI_EVENT)
		{
			switch (event.GUIEvent.EventType)
			{
			case irr::gui::EGUI_EVENT_TYPE::EGET_MESSAGEBOX_OK:
			{
				if (event.GUIEvent.Caller->getID() == EXIT_GAME_MESSAGE)
				{
					exit(EXIT_GAME_MESSAGE);
				}
			}
			default:
				return false;
			}
		}

		return false;
	}

	void BaseLevel::switchToLevel(LevelType type, map<wstring, wstring> params) {
		_switchLevelCallback(type, params);
	}

	void BaseLevel::_exitWithMessage(std::wstring& message)
	{
		_guiEnvironment->clear();

		_guiEnvironment->addMessageBox(L"Message", message.c_str(), true, 1, nullptr, EXIT_GAME_MESSAGE);
	}
}