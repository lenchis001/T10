#ifndef RESOURCE_LOADING_SERVICE_H
#define RESOURCE_LOADING_SERVICE_H

#include "IResourceLoadingService.h"

#include "boost/filesystem.hpp"

namespace T10::BLL::Services::ResourceLoading {

	class ResourceLoadingService : public IResourceLoadingService {
	public:
		ResourceLoadingService(
			boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
			boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment);

		bool loadScene(std::wstring& path, boost::shared_ptr<irr::scene::ISceneNode> root = nullptr) override;
		void loadGui(std::wstring& path) override;
		boost::shared_ptr<irr::scene::ISceneNode> loadTank(const std::wstring& name, int id = -1) override;

	private:
		void _patchWorkingDirectory(const boost::filesystem::path& pathToFile);
		void _unpatchWorkingDirectory();

		std::wstring _workingDirectoryBuffer;
		boost::shared_ptr<irr::scene::ISceneManager> _sceneManager;
		boost::shared_ptr<irr::gui::IGUIEnvironment> _guiEnvironment;
	};
}

#endif // RESOURCE_LOADING_SERVICE_H