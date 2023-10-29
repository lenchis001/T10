#ifndef _LOADING_SPLASH_AWARE_MIXIN_
#define _LOADING_SPLASH_AWARE_MIXIN_

#include "list"

#include "irrlicht.h"

namespace T10::Levels::Mixins {
	class LoadingSplashAwareMixin {
	public:
		LoadingSplashAwareMixin(boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment) {
			_rootGuiElement = guiEnvironment->getRootGUIElement();
		}
	protected:
		void _showLoadingSpalsh(std::wstring message = L"Please wait...") {
			for (auto guiElement : _rootGuiElement->getChildren()) {
				if (guiElement->isVisible()) {
					guiElement->setVisible(false);

					_hiddenElement.push_back(guiElement);
				}
			}
		}

		void _hideLoadingSpalsh() {
			for (auto guiElement : _hiddenElement) {
				guiElement->setVisible(true);
			}

			_hiddenElement.clear();
		}
	private:
		boost::shared_ptr<irr::gui::IGUIElement> _rootGuiElement;
		std::list<boost::shared_ptr<irr::gui::IGUIElement>> _hiddenElement;
	};
}

#endif // !_LOADING_SPLASH_AWARE_MIXIN_