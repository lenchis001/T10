#ifndef GARAGE_LEVEL
#define GARAGE_LEVEL

#include "iostream"

#include "boost/smart_ptr.hpp"
#include "boost/function.hpp"

#include "Levels/BaseLevel.hpp"

#include "Levels/Mixins/LoadingSplashAwareMixing.hpp"

#include "BLL/Services/User/IUserService.h"
#include "BLL/Services/Tank/ITankService.h"

#include "Cameras/GarageCameraAnimator.hpp"

namespace T10::Levels::Garage
{
#define TANKS_LIST_CONTROL 1
#define GO_TO_BATTLE_CONTROL 2
#define USER_NAME_CONTROL 3
#define MONEY_VALUE_CONTROL 4
#define BUY_TANK_CONTROL 5
#define BUY_TANK_DIALOG_CONTROL 6
#define GARAGE_UI 7

	class GarageLevel : public BaseLevel, public Mixins::LoadingSplashAwareMixin, public boost::enable_shared_from_this<ILevel>
	{
	public:
		GarageLevel(
			boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
			boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment,
			boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
			boost::shared_ptr<BLL::Services::User::IUserService> userService,
			boost::shared_ptr<BLL::Services::Tanks::ITankService> tankService,
			SwitchLevelCallbackFunction switchLevelCallback) : BaseLevel(sceneManager, guiEnvironment, functionsProcessingAware, switchLevelCallback),
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

		bool OnEvent(const irr::SEvent &event) override
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
						_goToBattle();
						return true;

					case BUY_TANK_CONTROL:
						_showTanksBuyDialog();
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
						_onTankSelected();
						return true;
					}

					break;
				}
				case irr::gui::EGUI_EVENT_TYPE::EGET_ELEMENT_CLOSED:
				{
					if (event.GUIEvent.Caller->getID() == BUY_TANK_DIALOG_CONTROL)
					{
						_unlockGarageGui();
						break;
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
		std::vector<BLL::Models::Tanks::Tank> _allTanks;
		std::vector<BLL::Models::Tanks::TankAssignment>> _myTanks;
		int _selectedTankIndex = -1;

		boost::shared_ptr<BLL::Services::User::IUserService> _userService;
		boost::shared_ptr<BLL::Services::Tanks::ITankService> _tankService;

		void _createUi()
		{
			std::wstring path = L"Resources/Levels/Garage/GUI/Garage.xml";
			_loadGui(path);

			auto rootGuiElement = _guiEnvironment->getRootGUIElement();
			_garageGui = rootGuiElement->getElementFromId(GARAGE_UI);

			boost::shared_ptr<irr::gui::IGUIElement> element = rootGuiElement->getElementFromId(TANKS_LIST_CONTROL, true);
			_tanksList = boost::static_pointer_cast<irr::gui::IGUIListBox>(element);

			_showLoadingSpalsh();

			_functionsProcessingAware->addFuctionToQueue(
				ThreadTypes::THREAD_POOL,
				[&, rootGuiElement]()
				{
					boost::shared_ptr<BLL::Models::DataActionResult<BLL::Models::User::Info>> userInfo = _userService->getInfo();

					boost::shared_ptr<BLL::Models::DataActionResult<std::vector<BLL::Models::Tanks::Tank>>> allTank = _tankService->getAll();
					if (!allTank->isOk())
					{
						std::wstring message(L"Cannot get tanks info.");

						_exitWithMessage(message);
						return;
					}
					_allTanks = allTank->getData();

					boost::shared_ptr<BLL::Models::DataActionResult<std::vector<BLL::Models::Tanks::TankAssignment>>> myTanks = _tankService->getMy();
					if (!myTanks->isOk())
					{
						std::wstring message(L"Cannot get user's tanks info.");

						_exitWithMessage(message);
						return;
					}

					_functionsProcessingAware->addFuctionToQueue(
						ThreadTypes::RENDER_THREAD,
						[&, userInfo, rootGuiElement]()
						{
							boost::shared_ptr<irr::gui::IGUIElement> element;

							element = rootGuiElement->getElementFromId(USER_NAME_CONTROL, true);
							boost::shared_ptr<irr::gui::IGUIStaticText> userNameLabel = boost::static_pointer_cast<irr::gui::IGUIStaticText>(element);
							userNameLabel->setText(userInfo->getData().getName().c_str());

							element = rootGuiElement->getElementFromId(MONEY_VALUE_CONTROL, true);
							boost::shared_ptr<irr::gui::IGUIStaticText> moneyLabel = boost::static_pointer_cast<irr::gui::IGUIStaticText>(element);
							moneyLabel->setText(std::to_wstring(userInfo->getData().getMoney()).c_str());

							for (const BLL::Models::Tanks::Tank tank : _allTanks)
							{
								_tanksList->addItem(tank.getName().c_str());
							}

							_hideLoadingSpalsh();
						});
				});
		}

		void _createScene()
		{
			std::wstring path = L"Resources/Levels/Garage/Garage.irr";
			_loadScene(path);

			_sceneManager->addCameraSceneNode()->addAnimator(
				boost::make_shared<T10::Levels::Garage::Cameras::GarageCameraAnimator>(irr::core::vector3df(0, 0, 0), 10));
		}

		void _goToBattle()
		{
			irr::s32 selectedTankIndex = _tanksList->getSelected();

			if (selectedTankIndex != -1)
			{
			}
		}

		void _onTankSelected()
		{
			_selectedTankIndex = _tanksList->getSelected();

			auto tank = _allTanks[_selectedTankIndex];

			auto modelPath = std::wstring(L"Resources/Models/Tanks/") + tank.getName() + std::wstring(L"/Tank.obj");

			auto mesh = _sceneManager->getMesh(modelPath.c_str());
			_sceneManager->addMeshSceneNode(mesh);
		}

		void _showTanksBuyDialog()
		{
			_lockGarageGui();

			_showLoadingSpalsh();

			std::wstring path = L"Resources/Levels/Garage/GUI/TankBuy.xml";
			_loadGui(path);

			// _functionsProcessingAware->addFuctionToQueue(
			// 	ThreadTypes::THREAD_POOL,
			// 	[&, rootGuiElement]()
			// 	{

			// 	});

			_hideLoadingSpalsh();
		}

		void _lockGarageGui()
		{
			_garageGui->setVisible(false);

			_tankService->getAll();
		}

		void _unlockGarageGui()
		{
			_garageGui->setVisible(true);
		}
	};
}

#endif