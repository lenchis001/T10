#ifndef BATTLE_LEVEL
#define BATTLE_LEVEL

#include "iostream"

#include "boost/smart_ptr.hpp"
#include "boost/function.hpp"

#include "Levels/BaseLevel.hpp"

#include "Levels/Mixins/LoadingSplashAwareMixing.hpp"

#include "BLL/Services/User/IUserService.h"
#include "BLL/Services/BattleState/IBattleStateSynchronizationService.h"

#include "Levels/Garage/BuyTankDialogController.hpp"

namespace T10::Levels::Battle
{
#define AIM_CONTROL 1

	class BattleLevel : public BaseLevel, public Mixins::LoadingSplashAwareMixin, public boost::enable_shared_from_this<ILevel>
	{
	public:
		BattleLevel(
			boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
			boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment,
			boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
			boost::shared_ptr<BLL::Services::ResourceLoading::IResourceLoadingService> resourceLoadingService,
			boost::shared_ptr<irr::gui::ICursorControl> cursorControl,
			boost::shared_ptr<BLL::Services::BattleState::IBattleStateSynchronizationService> battleStateSynchronizationService,
			SwitchLevelCallbackFunction switchLevelCallback)
			: BaseLevel(sceneManager, guiEnvironment, functionsProcessingAware, resourceLoadingService, switchLevelCallback),
			Mixins::LoadingSplashAwareMixin(guiEnvironment)
		{
			_cursorControl = cursorControl;
			_battleStateSynchronizationService = battleStateSynchronizationService;
		}

		void onLoadRequested() override
		{
			_createUi();
			_createScene();

			_battleStateSynchronizationService->joinBattle("ws://localhost:8080", "33e9e476-69c9-4bc3-9eb5-3ff0de6cebee");
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
			else if (event.EventType == irr::EEVENT_TYPE::EET_KEY_INPUT_EVENT && _battleStateSynchronizationService->OnEvent(event.KeyInput))
			{
				return true;
			}

			return BaseLevel::OnEvent(event);
		}

	private:
		boost::shared_ptr<BLL::Services::BattleState::IBattleStateSynchronizationService> _battleStateSynchronizationService;
		boost::shared_ptr<irr::gui::ICursorControl> _cursorControl;

		void _createUi()
		{
			std::wstring path = L"Resources/GUI/Battle/Status.xml";
			_resourceLoadingService->loadGui(path);

			path = L"Resources/GUI/Battle/Aim.xml";
			_resourceLoadingService->loadGui(path);

			_centerAim();
		}

		void _createScene()
		{
			
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