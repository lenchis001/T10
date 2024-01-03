#ifndef IRESOURCE_LOADING_SERVICE
#define IRESOURCE_LOADING_SERVICE

#include "string"

#include "boost/smart_ptr.hpp"

#include "irrlicht.h"

namespace T10::BLL::Services::ResourceLoading {

	class IResourceLoadingService {
	public:
		virtual bool loadScene(std::wstring& path, boost::shared_ptr<irr::scene::ISceneNode> root = nullptr) = 0;

		virtual void loadGui(std::wstring& path) = 0;

		virtual boost::shared_ptr<irr::scene::ISceneNode> loadTank(const std::wstring& name, int id = -1) = 0;
	};

}

#endif // IRESOURCE_LOADING_SERVICE