#ifndef _SIGNINLEVEL_H_
#define _SIGNINLEVEL_H_

#include "Levels/BaseLevel.h"
#include "BLL/Services/User/IUserService.h"

#define EMAIL_FIELD 1
#define PASSWORD_FIELD 2
#define SIGN_IN_BUTTON 3

namespace T10::Levels::SignIn
{
    class SignInLevel : public BaseLevel
    {
    public:
        SignInLevel(
            boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
            boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment,
            boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
            boost::shared_ptr<BLL::Services::ResourceLoading::IResourceLoadingService> resourceLoadingService,
            boost::shared_ptr<BLL::Services::User::IUserService> userService,
            SwitchLevelCallbackFunction switchLevelCallback);

        virtual void onLoadRequested() override;
        virtual void onUnloadRequested() override;
        bool OnEvent(const irr::SEvent& event) override;

    private:
        void _signIn(std::wstring email, std::wstring password);
        void _goToGarage();

        boost::shared_ptr<BLL::Services::User::IUserService> _userService;
        boost::shared_ptr<irr::gui::IGUIImage> _backgroundImage;
    };
}

#endif // _SIGNINLEVEL_H_