#ifndef BATTLE_LEVEL
#define BATTLE_LEVEL

#include "iostream"

#include "boost/smart_ptr.hpp"
#include "boost/function.hpp"

#include "Levels/BaseLevel.hpp"

#include "Levels/Mixins/LoadingSplashAwareMixing.hpp"
#include "Levels/Mixins/TankLoadingAware.hpp"

#include "BLL/Services/User/IUserService.h"
#include "BLL/Services/BattleState/EventRedirectionService.hpp"

#include "Levels/Garage/BuyTankDialogController.hpp"

namespace T10::Levels::Battle
{
#define AIM_CONTROL 1

	class BattleLevel : public Mixins::TankLoadingAware, public Mixins::LoadingSplashAwareMixin, public boost::enable_shared_from_this<ILevel>
	{
	public:
		BattleLevel(
			boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
			boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment,
			boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
			boost::shared_ptr<irr::gui::ICursorControl> cursorControl,
			boost::shared_ptr<BLL::Services::BattleState::EventRedirectionService> eventRedirectionService,
			SwitchLevelCallbackFunction switchLevelCallback)
			: Mixins::TankLoadingAware(sceneManager, guiEnvironment, functionsProcessingAware, switchLevelCallback),
			Mixins::LoadingSplashAwareMixin(guiEnvironment)
		{
			_cursorControl = cursorControl;
			_eventRedirectionService = eventRedirectionService;
		}

		void onLoadRequested() override
		{
			_createUi();
			_createScene();
		}

		void onUnloadRequested() override
		{
		}

		bool OnEvent(const irr::SEvent& event) override
		{
			if (event.EventType == irr::EEVENT_TYPE::EET_GUI_EVENT)
			{
				switch (event.GUIEvent.EventType)
				{
				case irr::gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED:
				{
					boost::shared_ptr<irr::gui::IGUIButton> button = boost::static_pointer_cast<irr::gui::IGUIButton>(event.GUIEvent.Caller);

					switch (event.GUIEvent.Caller->getID())
					{
					case GO_TO_BATTLE_CONTROL:
						return true;

					case BUY_TANK_CONTROL:
						return true;

					default:
						break;
					}

					break;
				}
				case irr::gui::EGUI_EVENT_TYPE::EGET_LISTBOX_CHANGED:
				{
					if (event.GUIEvent.Caller->getID() == TANKS_LIST_CONTROL)
					{
						return true;
					}

					break;
				}
				default:
					break;
				}
			}
			else if (event.EventType == irr::EEVENT_TYPE::EET_KEY_INPUT_EVENT && _eventRedirectionService->OnEvent(event.KeyInput))
			{
				return true;
			}

			return BaseLevel::OnEvent(event);
		}

	private:
		boost::shared_ptr<BLL::Services::BattleState::EventRedirectionService> _eventRedirectionService;
		boost::shared_ptr<irr::gui::ICursorControl> _cursorControl;

		void _createUi()
		{
			std::wstring path = L"Resources/GUI/Battle/Status.xml";
			_loadGui(path);

			path = L"Resources/GUI/Battle/Aim.xml";
			_loadGui(path);

			_centerAim();
		}

		void _createScene()
		{
			std::wstring path = L"Resources/Levels/Testgrad/Testgrad.irr";
			_loadScene(path);

			auto tank = _loadTank(L"T-1");
			auto body = _sceneManager->getSceneNodeFromName("Body", tank);
			body->setID(123);

			auto camera = _sceneManager->addCameraSceneNode();
			// auto tankMovingAnimator = boost::make_shared<Tank::CurrentPlayerTankMovingAnimator>(body, 0.01F, 0.04F);

			camera->addAnimator(
				boost::make_shared<T10::Levels::Cameras::GarageCameraAnimator>(body, 5, 7, 15, 0.2F, irr::core::HALF_PI + 0.2, 300, 0.85F, 1.2F, 3, nullptr));
		}

		void _centerAim()
		{
			auto aim = _guiEnvironment->getRootGUIElement()->getElementFromId(AIM_CONTROL);

			auto parentRect = aim->getParent()->getAbsoluteClippingRect().getSize();
			auto rect = aim->getAbsolutePosition().getSize();

			aim->setRelativePosition(parentRect / 2 - rect / 2);
		}
	};
}

#endif // BATTLE_LEVEL