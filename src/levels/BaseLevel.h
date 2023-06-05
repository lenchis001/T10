#pragma once

#include "string"
#include "map"

#include "boost/smart_ptr.hpp"
#include "boost/functional.hpp"
#include "boost/filesystem.hpp"

#include "ILevel.h"
#include "Types.h"

using namespace std;

namespace T10 {
	class BaseLevel : public ILevel {
	public:
		BaseLevel(boost::shared_ptr<irr::scene::ISceneManager> sceneManager, boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment, SwitchLevelCallbackFunction switchLevelCallback);

		virtual void load();

		virtual void onLoadRequested() = 0;
		virtual void onUnloadRequested() = 0;

		bool OnEvent(const irr::SEvent& event) override;
	protected:
		virtual void switchToLevel(LevelType type, map<wstring, wstring> params);

		void _loadScene(std::wstring& path);
		void _loadGui(std::wstring& path);

		boost::shared_ptr<irr::scene::ISceneManager> _sceneManager;
		boost::shared_ptr<irr::gui::IGUIEnvironment> _guiEnvironment;
	private:
		void _patchWorkingDirectory(const boost::filesystem::path& pathToFile);
		void _unpatchWorkingDirectory();

		SwitchLevelCallbackFunction _switchLevelCallback;
		std::wstring _workingDirectoryBuffer;
	};
}