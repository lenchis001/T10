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
            _userService = userService;
        }

        virtual void onLoadRequested() override
        {
            _userService->signIn(L"leontii1996@mail.ru", L"Boost2017");
            auto info = _userService->getInfo();

            info->getData();
        }

        virtual void onUnloadRequested() override
        {
        }

    private:
        boost::shared_ptr<BLL::Services::User::IUserService> _userService;
    };
}