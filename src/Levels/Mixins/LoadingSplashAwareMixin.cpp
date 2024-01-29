#include "LoadingSplashAwareMixin.h"

namespace T10::Levels::Mixins {
    LoadingSplashAwareMixin::LoadingSplashAwareMixin(boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment) {
        _rootGuiElement = guiEnvironment->getRootGUIElement();
    }

    void LoadingSplashAwareMixin::_showLoadingSpalsh(std::wstring message) {
        for (auto guiElement : _rootGuiElement->getChildren()) {
            if (guiElement->isVisible()) {
                guiElement->setVisible(false);
                _hiddenElement.push_back(guiElement);
            }
        }
    }

    void LoadingSplashAwareMixin::_hideLoadingSpalsh() {
        for (auto guiElement : _hiddenElement) {
            guiElement->setVisible(true);
        }
        _hiddenElement.clear();
    }
}