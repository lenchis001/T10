#ifndef RESOURCE_LOADING_SERVICE
#define RESOURCE_LOADING_SERVICE

#include "IResourceLoadingService.h"

namespace T10::BLL::Services::ResourceLoading {

	class ResourceLoadingService : public IResourceLoadingService {
	public:
		ResourceLoadingService(
			boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
			boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment) {
			_sceneManager = sceneManager;
			_guiEnvironment = guiEnvironment;
		}

		bool loadScene(std::wstring& path, boost::shared_ptr<irr::scene::ISceneNode> root = nullptr) override
		{
			auto absolutePath = boost::filesystem::absolute(path);
			_patchWorkingDirectory(absolutePath);

			auto result = _sceneManager->loadScene(absolutePath.c_str(), nullptr, root);

			_unpatchWorkingDirectory();

			return result;
		}

		void loadGui(std::wstring& path) override
		{
			auto absolutePath = boost::filesystem::absolute(path);
			_patchWorkingDirectory(absolutePath);

			_guiEnvironment->loadGUI(absolutePath.c_str());

			_unpatchWorkingDirectory();
		}

		boost::shared_ptr<irr::scene::ISceneNode> loadTank(const std::wstring& name, int id = -1) override {
			auto modelPath = std::wstring(L"Resources/Models/Tanks/") + name + L"/" + name + L".irr";

			auto selectedTankRoot = _sceneManager->addEmptySceneNode();
			loadScene(modelPath, selectedTankRoot);

			selectedTankRoot->setID(id);
			selectedTankRoot->setVisible(true);
			selectedTankRoot->setScale(irr::core::vector3df(1));

			return selectedTankRoot;
		}
	private:
		void _patchWorkingDirectory(const boost::filesystem::path& pathToFile)
		{
			_workingDirectoryBuffer = boost::filesystem::current_path().wstring();

			auto levelFileDirectory = pathToFile.parent_path();

			boost::filesystem::current_path(levelFileDirectory);
		}

		void _unpatchWorkingDirectory()
		{
			boost::filesystem::current_path(_workingDirectoryBuffer.c_str());
		}

		std::wstring _workingDirectoryBuffer;
		boost::shared_ptr<irr::scene::ISceneManager> _sceneManager;
		boost::shared_ptr<irr::gui::IGUIEnvironment> _guiEnvironment;
	};

}

#endif // RESOURCE_LOADING_SERVICE