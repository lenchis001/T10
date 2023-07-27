#include "levels/BaseLevel.h"

namespace T10::Levels
{
    class SignInLevel : public BaseLevel
    {
    public:
        SignInLevel(
            boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
            boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment,
            boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
            boost::shared_ptr<BLL::Services::User::IUserService> userService,
            SwitchLevelCallbackFunction switchLevelCallback);
    }
}