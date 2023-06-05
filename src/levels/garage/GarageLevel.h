#pragma once

#include "levels/BaseLevel.h"

#include "boost/smart_ptr.hpp"
#include "boost/function.hpp"

namespace T10 {
	class GarageLevel : public BaseLevel, public boost::enable_shared_from_this<ILevel> {
	public:
		GarageLevel(boost::shared_ptr<irr::scene::ISceneManager> sceneManager, boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment, SwitchLevelCallbackFunction switchLevelCallback);

		void onLoadRequested() override;
		void onUnloadRequested() override;

		bool OnEvent(const irr::SEvent& event) override;
	private:
		void _createUi();
		void _createScene();

		void _goToBattle(irr::gui::IGUIButton* button);
	};
}