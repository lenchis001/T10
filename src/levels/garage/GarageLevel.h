#pragma once

#include "levels/BaseLevel.h"

#include "boost/smart_ptr.hpp"
#include "boost/function.hpp"

#include "bll/services/User/IUserService.h"

namespace T10
{
	class GarageLevel : public BaseLevel, public boost::enable_shared_from_this<ILevel>
	{
	public:
		GarageLevel(
			boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
			boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment,
			boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
			boost::shared_ptr<bll::services::User::IUserService> userService,
			SwitchLevelCallbackFunction switchLevelCallback);

		void onLoadRequested() override;
		void onUnloadRequested() override;

		bool OnEvent(const irr::SEvent &event) override;

	private:
		boost::shared_ptr<irr::gui::IGUIListBox> _tanksList;

		boost::shared_ptr<bll::services::User::IUserService> _userService;

		void _createUi();
		void _createScene();

		void _goToBattle();
	};
}