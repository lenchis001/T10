#ifndef LOADING_SPLASH_AWARE_MIXIN
#define LOADING_SPLASH_AWARE_MIXIN

#include "list"
#include "irrlicht.h"
#include "boost/shared_ptr.hpp"

namespace T10::Levels::Mixins {
    class LoadingSplashAwareMixin {
    public:
        LoadingSplashAwareMixin(boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment);
    protected:
        void _showLoadingSpalsh(std::wstring message = L"Please wait...");
        void _hideLoadingSpalsh();
    private:
        boost::shared_ptr<irr::gui::IGUIElement> _rootGuiElement;
        std::list<boost::shared_ptr<irr::gui::IGUIElement>> _hiddenElement;
    };
}

#endif // LOADING_SPLASH_AWARE_MIXIN