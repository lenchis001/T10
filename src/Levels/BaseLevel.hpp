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
			SwitchLevelCallbackFunction switchLevelCallback) : _sceneManager(sceneManager),
															   _guiEnvironment(guiEnvironment),
															   _functionsProcessingAware(functionsProcessingAware),
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

		void _loadScene(std::wstring &path)
		{
			auto absolutePath = boost::filesystem::absolute(path);
			_patchWorkingDirectory(absolutePath);

			_sceneManager->loadScene(absolutePath.c_str());

			_unpatchWorkingDirectory();
		}

		void _loadGui(std::wstring &path)
		{
			auto absolutePath = boost::filesystem::absolute(path);
			_patchWorkingDirectory(absolutePath);

			_guiEnvironment->loadGUI(absolutePath.c_str());

			_unpatchWorkingDirectory();
		}

		void _exitWithMessage(std::wstring &message)
		{
			_guiEnvironment->clear();

			_guiEnvironment->addMessageBox(L"Message", message.c_str(), true, 1, nullptr, EXIT_GAME_MESSAGE);
		}

		boost::shared_ptr<irr::scene::ISceneManager> _sceneManager;
		boost::shared_ptr<irr::gui::IGUIEnvironment> _guiEnvironment;
		boost::shared_ptr<IFunctionsProcessingAware> _functionsProcessingAware;

	private:
		void _patchWorkingDirectory(const boost::filesystem::path &pathToFile)
		{
			_workingDirectoryBuffer = boost::filesystem::current_path().wstring();

			auto levelFileDirectory = pathToFile.parent_path();

			boost::filesystem::current_path(levelFileDirectory);
		}

		void _unpatchWorkingDirectory()
		{
			boost::filesystem::current_path(_workingDirectoryBuffer.c_str());
		}

		SwitchLevelCallbackFunction _switchLevelCallback;
		std::wstring _workingDirectoryBuffer;
	};
}

#endif