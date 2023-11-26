#ifndef BATTLE_LEVEL
#define BATTLE_LEVEL

#include "iostream"

#include "boost/smart_ptr.hpp"
#include "boost/function.hpp"

#include "Levels/BaseLevel.hpp"
#include "Tank/TankMovingAnimator.hpp"

#include "Levels/Mixins/LoadingSplashAwareMixing.hpp"
#include "Levels/Mixins/TankLoadingAware.hpp"

#include "BLL/Services/User/IUserService.h"
#include "BLL/Services/Tank/ITankService.h"
#include "BLL/Services/TankAssignment/ITankAssignmentService.h"

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
			boost::shared_ptr<BLL::Services::User::IUserService> userService,
			boost::shared_ptr<BLL::Services::Tanks::ITankService> tankService,
			SwitchLevelCallbackFunction switchLevelCallback) : Mixins::TankLoadingAware(sceneManager, guiEnvironment, functionsProcessingAware, switchLevelCallback),
			Mixins::LoadingSplashAwareMixin(guiEnvironment)
		{
			_userService = userService;
			_tankService = tankService;
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

			return BaseLevel::OnEvent(event);
		}

	private:
		boost::shared_ptr<irr::gui::IGUIElement> _garageGui;
		boost::shared_ptr<irr::gui::IGUIListBox> _tanksList;
		boost::shared_ptr<const std::vector<BLL::Models::Tanks::Tank>> _allTanks;
		boost::shared_ptr<std::vector<BLL::Models::TankAssignments::TankAssignment>> _myTanks;
		int _selectedTankIndex = -1;

		boost::shared_ptr<BLL::Services::User::IUserService> _userService;
		boost::shared_ptr<BLL::Services::Tanks::ITankService> _tankService;
		boost::shared_ptr<BLL::Services::TankAssignment::ITankAssignmentService> _tankAssignmentService;

		void _createUi()
		{
			std::wstring path = L"Resources/GUI/Battle/Status.xml";
			_loadGui(path);

			path = L"Resources/GUI/Battle/Aim.xml";
			_loadGui(path);

			_centerAim();

			auto rootGuiElement = _guiEnvironment->getRootGUIElement();
			_garageGui = rootGuiElement->getElementFromId(GARAGE_UI);

			boost::shared_ptr<irr::gui::IGUIElement> element = rootGuiElement->getElementFromId(TANKS_LIST_CONTROL, true);
			_tanksList = boost::static_pointer_cast<irr::gui::IGUIListBox>(element);
		}

		void _createScene()
		{
			std::wstring path = L"Resources/Levels/Testgrad/Testgrad.irr";
			_loadScene(path);

			auto tank = _loadTank(L"T-1");
			auto body = _sceneManager->getSceneNodeFromName("Body", tank);

			auto camera = _sceneManager->addCameraSceneNode();
			//camera->setParent(body);
			auto tankMovingAnimator = boost::make_shared<Tank::TankMovingAnimator>(body, 0.01F, 0.04F);

			camera->addAnimator(
				boost::make_shared<T10::Levels::Cameras::GarageCameraAnimator>(body, 5, 7, 15, 0.2F, irr::core::HALF_PI + 0.2, 300, 0.85F, 1.2F, 3, tankMovingAnimator));
		}

		void _centerAim() {
			auto aim = _guiEnvironment->getRootGUIElement()->getElementFromId(AIM_CONTROL);

			auto parentRect = aim->getParent()->getAbsoluteClippingRect().getSize();
			auto rect = aim->getAbsolutePosition().getSize();

			aim->setRelativePosition(parentRect / 2 - rect / 2);
		}
	};
}

#endif // BATTLE_LEVEL