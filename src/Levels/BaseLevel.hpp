#ifndef BASE_LEVEL
#define BASE_LEVEL

#pragma once

#include "string"
#include "map"

#include "boost/smart_ptr.hpp"
#include "boost/functional.hpp"
#include "boost/filesystem.hpp"

#include "IFunctionsProcessingAware.h"

#include "ILevel.h"
#include "Types.h"

#include "BLL/Services/ResourceLoading/IResourceLoadingService.h"

using namespace std;

namespace T10::Levels
{
#define EXIT_GAME_MESSAGE 10001

	class BaseLevel : public ILevel
	{
	public:
		BaseLevel(
			boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
			boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment,
			boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
			boost::shared_ptr<BLL::Services::ResourceLoading::IResourceLoadingService> resourceLoadingService,
			SwitchLevelCallbackFunction switchLevelCallback) : _sceneManager(sceneManager),
															   _guiEnvironment(guiEnvironment),
															   _functionsProcessingAware(functionsProcessingAware),
															   _resourceLoadingService(resourceLoadingService),
															   _switchLevelCallback(switchLevelCallback) {}

		virtual void load()
		{
		}

		bool OnEvent(const irr::SEvent &event) override
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

	protected:
		virtual void switchToLevel(LevelType type, map<wstring, wstring> params)
		{
			_switchLevelCallback(type, params);
		}

		void _exitWithMessage(std::wstring &message)
		{
			_guiEnvironment->clear();

			_guiEnvironment->addMessageBox(L"Message", message.c_str(), true, 1, nullptr, EXIT_GAME_MESSAGE);
		}

		boost::shared_ptr<irr::scene::ISceneManager> _sceneManager;
		boost::shared_ptr<irr::gui::IGUIEnvironment> _guiEnvironment;
		boost::shared_ptr<IFunctionsProcessingAware> _functionsProcessingAware;
		boost::shared_ptr<BLL::Services::ResourceLoading::IResourceLoadingService> _resourceLoadingService;
	private:
		SwitchLevelCallbackFunction _switchLevelCallback;
	};
}

#endif // BASE_LEVEL