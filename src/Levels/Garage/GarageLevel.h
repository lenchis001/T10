#pragma once

#include "levels/BaseLevel.h"

#include "boost/smart_ptr.hpp"
#include "boost/function.hpp"

#include "BLL/Services/User/IUserService.h"
#include "BLL/Services/Tank/ITankService.h"

namespace T10
{
	class GarageLevel : public BaseLevel, public boost::enable_shared_from_this<ILevel>
	{
	public:
		GarageLevel(
			boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
			boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment,
			boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
			boost::shared_ptr<BLL::Services::User::IUserService> userService,
			boost::shared_ptr<BLL::Services::Tanks::ITankService> tankService,
			SwitchLevelCallbackFunction switchLevelCallback);

		void onLoadRequested() override;
		void onUnloadRequested() override;

		bool OnEvent(const irr::SEvent &event) override;

	private:
		boost::shared_ptr<irr::gui::IGUIListBox> _tanksList;

		boost::shared_ptr<BLL::Services::User::IUserService> _userService;
		boost::shared_ptr<BLL::Services::Tanks::ITankService> _tankService;

		void _createUi();
		void _createScene();

		void _goToBattle();
		void _onTankSelected();
	};
}