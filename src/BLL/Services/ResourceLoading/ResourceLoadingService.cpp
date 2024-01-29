#include "ResourceLoadingService.h"

using namespace T10::BLL::Services::ResourceLoading;

ResourceLoadingService::ResourceLoadingService(
	boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
	boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment)
{
	_sceneManager = sceneManager;
	_guiEnvironment = guiEnvironment;
}

bool ResourceLoadingService::loadScene(std::wstring& path, boost::shared_ptr<irr::scene::ISceneNode> root)
{
	auto absolutePath = boost::filesystem::absolute(path);
	_patchWorkingDirectory(absolutePath);

	auto result = _sceneManager->loadScene(absolutePath.c_str(), nullptr, root);

	_unpatchWorkingDirectory();

	return result;
}

void ResourceLoadingService::loadGui(std::wstring& path)
{
	auto absolutePath = boost::filesystem::absolute(path);
	_patchWorkingDirectory(absolutePath);

	_guiEnvironment->loadGUI(absolutePath.c_str());

	_unpatchWorkingDirectory();
}

boost::shared_ptr<irr::scene::ISceneNode> ResourceLoadingService::loadTank(
	const std::wstring& name,
	int id)
{
	auto modelPath = std::wstring(L"Resources/Models/Tanks/") + name + L"/" + name + L".irr";
	auto selectedTankRoot = _sceneManager->addEmptySceneNode();
	loadScene(modelPath, selectedTankRoot);
	selectedTankRoot->setID(id);
	selectedTankRoot->setVisible(true);
	selectedTankRoot->setScale(irr::core::vector3df(1));

	return selectedTankRoot;
}

void ResourceLoadingService::_patchWorkingDirectory(const boost::filesystem::path& pathToFile)
{
	_workingDirectoryBuffer = boost::filesystem::current_path().wstring();
	auto levelFileDirectory = pathToFile.parent_path();
	boost::filesystem::current_path(levelFileDirectory);
}

void ResourceLoadingService::_unpatchWorkingDirectory()
{
	boost::filesystem::current_path(_workingDirectoryBuffer.c_str());
}