#include "Levels/BaseLevel.hpp"
#include "BLL/Services/User/IUserService.h"

namespace T10::Levels::SignIn
{
    class SignInLevel : public BaseLevel
    {
    public:
        SignInLevel(
            boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
            boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment,
            boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
            boost::shared_ptr<BLL::Services::User::IUserService> userService,
            SwitchLevelCallbackFunction switchLevelCallback) 
            : BaseLevel(sceneManager, guiEnvironment, functionsProcessingAware, switchLevelCallback)
        {
        }

        virtual void onLoadRequested() override
        {
        }

        virtual void onUnloadRequested() override
        {
        }
    };
}