#ifndef TANK_LOADING_AWARE
#define TANK_LOADING_AWARE

#include "string"
#include "irrlicht.h"
#include "Levels/BaseLevel.hpp"

namespace T10::Levels::Mixins {

	class TankLoadingAware : public BaseLevel {
	public:
		TankLoadingAware(boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
			boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment,
			boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
			SwitchLevelCallbackFunction switchLevelCallback): BaseLevel(sceneManager,guiEnvironment,functionsProcessingAware,switchLevelCallback) {}

	protected:
		boost::shared_ptr<irr::scene::ISceneNode> _loadTank(const std::wstring& name, int id = -1) {
			auto modelPath = std::wstring(L"Resources/Models/Tanks/") + name + L"/" + name + L".irr";

			auto selectedTankRoot = _sceneManager->addEmptySceneNode();
			_loadScene(modelPath, selectedTankRoot);

			selectedTankRoot->setID(id);
			selectedTankRoot->setVisible(true);
			selectedTankRoot->setScale(irr::core::vector3df(1));

			return selectedTankRoot;
		}
	};

}

#endif