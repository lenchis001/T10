#ifndef __SCENE_MANAGER_AWARE__
#define __SCENE_MANAGER_AWARE__

#include "IReferenceCounted.h"

namespace irr::scene {
	class ISceneManager;

	template<class S = ISceneManager> class SceneManagerAwareMixin
	{
	public:
		SceneManagerAwareMixin(boost::shared_ptr<S> sceneManager) {
			_sceneManager = sceneManager;
		}

		virtual boost::shared_ptr<S> getSceneManager() {
			return _sceneManager.lock();
		}

		virtual void setSceneManager(boost::shared_ptr<S> sceneManager) {
			_sceneManager = sceneManager;
		}
	private:
		boost::weak_ptr<S> _sceneManager;
	};
}

#endif