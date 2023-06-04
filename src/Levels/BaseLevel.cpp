#include "BaseLevel.h"

namespace GameLogic {
	BaseLevel::BaseLevel(boost::shared_ptr<irr::scene::ISceneManager> sceneManager, boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment, SwitchLevelCallbackFunction switchLevelCallback) :
		_sceneManager(sceneManager)
		, _guiEnvironment(guiEnvironment)
		, _switchLevelCallback(switchLevelCallback) { }

	void BaseLevel::load()
	{
	}

	bool BaseLevel::OnEvent(const irr::SEvent& event)
	{
		return false;
	}

	void BaseLevel::switchToLevel(LevelType type, map<wstring, wstring> params)
	{
		_switchLevelCallback(type, params);
	}

	void BaseLevel::_loadScene(std::wstring& path)
	{
		auto absolutePath = boost::filesystem::absolute(path);
		_patchWorkingDirectory(absolutePath);

		_sceneManager->loadScene(absolutePath.c_str());

		_unpatchWorkingDirectory();
	}

	void BaseLevel::_loadGui(std::wstring& path)
	{
		auto absolutePath = boost::filesystem::absolute(path);
		_patchWorkingDirectory(absolutePath);

		_guiEnvironment->loadGUI(absolutePath.c_str());

		_unpatchWorkingDirectory();
	}

	void BaseLevel::_patchWorkingDirectory(const boost::filesystem::path& pathToFile)
	{
		_workingDirectoryBuffer = boost::filesystem::current_path().wstring();

		auto levelFileDirectory = pathToFile.parent_path();

		boost::filesystem::current_path(levelFileDirectory);
	}

	void BaseLevel::_unpatchWorkingDirectory()
	{
		boost::filesystem::current_path(_workingDirectoryBuffer.c_str());
	}
}
