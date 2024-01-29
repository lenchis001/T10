#ifndef SETUP_SCENE_MESSAGE_HANDLER_H
#define SETUP_SCENE_MESSAGE_HANDLER_H

#include "MessageHandlerBase.h"
#include "irrlicht.h"
#include "boost/smart_ptr.hpp"
#include "IFunctionsProcessingAware.h"
#include "BLL/Services/ResourceLoading/IResourceLoadingService.h"
#include "BLL/Services/BattleState/TankMovingAnimator.h"
#include "BLL/Services/User/IUserService.h"

namespace T10::BLL::Services::BattleState::Tracking::MessageHandling::Handlers {

	class SetupSceneMessageHandler : public MessageHandlerBase {
	public:
		SetupSceneMessageHandler(
			boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
			boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
			boost::shared_ptr<BLL::Services::ResourceLoading::IResourceLoadingService> resourceLoadingService,
			boost::shared_ptr<BLL::Services::User::IUserService> userService);

		void handle(const boost::json::object& messageBody) override;

	private:
		void _setupTank(bool isCurrentUser, const std::string& name, int bodyId);
		std::wstring _toWstring(const std::string& value);

		boost::shared_ptr<IFunctionsProcessingAware> _functionsProcessingAware;
		boost::shared_ptr<irr::scene::ISceneManager> _sceneManager;
		boost::shared_ptr<BLL::Services::ResourceLoading::IResourceLoadingService> _resourceLoadingService;
		boost::shared_ptr<BLL::Services::User::IUserService> _userService;
	};

}

#endif // SETUP_SCENE_MESSAGE_HANDLER_H