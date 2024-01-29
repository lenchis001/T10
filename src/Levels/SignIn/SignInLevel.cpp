#include "SignInLevel.h"

namespace T10::Levels::SignIn {

    SignInLevel::SignInLevel(
        boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
        boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment,
        boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
        boost::shared_ptr<BLL::Services::ResourceLoading::IResourceLoadingService> resourceLoadingService,
        boost::shared_ptr<BLL::Services::User::IUserService> userService,
        SwitchLevelCallbackFunction switchLevelCallback)
        : BaseLevel(sceneManager, guiEnvironment, functionsProcessingAware, resourceLoadingService, switchLevelCallback)
    {
        _userService = userService;
    }

    void SignInLevel::onLoadRequested()
    {
        std::wstring path = L"Resources/Levels/SignIn/GUI/SignIn.xml";
        _resourceLoadingService->loadGui(path);

        if (_userService->signIn().getError() == BLL::Models::ErrorCode::OK) {
            _goToGarage();
        }
    }

    void SignInLevel::onUnloadRequested()
    {
        // Empty Body 
    }

    bool SignInLevel::OnEvent(const irr::SEvent& event)
    {
        if (event.EventType == irr::EEVENT_TYPE::EET_GUI_EVENT)
        {
            switch (event.GUIEvent.EventType)
            {
            case irr::gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED:
                if (event.GUIEvent.Caller->getID() == SIGN_IN_BUTTON)
                {
                    auto rootElement = _guiEnvironment->getRootGUIElement();
                    std::wstring email = rootElement->getElementFromId(EMAIL_FIELD, true)->getText();
                    std::wstring password = rootElement->getElementFromId(PASSWORD_FIELD, true)->getText();

                    _signIn(email, password);

                    return true;
                }
                break;
            default:
                return false;
            }
        }

        return false;
    }

    void SignInLevel::_signIn(std::wstring email, std::wstring password)
    {
        auto result = _userService->signIn(email, password);

        if (result.getError() == BLL::Models::OK) {
            _goToGarage();
        }
        else {
            _guiEnvironment->addMessageBox(
                L"An error occured.",
                L"An error occured on attempt to sign in. Please check your internet connection and credentials and try again.",
                true,
                1,
                _guiEnvironment->getRootGUIElement());
        }
    }

    void SignInLevel::_goToGarage()
    {
        switchToLevel(Levels::MENU, {});
    }
}