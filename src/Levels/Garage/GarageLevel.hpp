#ifndef GARAGE_LEVEL
#define GARAGE_LEVEL

#include "iostream"

#include "boost/smart_ptr.hpp"
#include "boost/function.hpp"

#include "Levels/BaseLevel.hpp"

#include "BLL/Services/User/IUserService.h"
#include "BLL/Services/Tank/ITankService.h"

#include "Cameras/GarageCameraAnimator.hpp"

namespace T10::Levels::Garage
{
	#define TANKS_LIST_CONTROL 1
	#define GO_TO_BATTLE_CONTROL 2
	#define USER_NAME_CONTROL 3
	#define MONEY_VALUE_CONTROL 4

	class GarageLevel : public BaseLevel, public boost::enable_shared_from_this<ILevel>
	{
	public:
		GarageLevel(
			boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
			boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment,
			boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
			boost::shared_ptr<BLL::Services::User::IUserService> userService,
			boost::shared_ptr<BLL::Services::Tanks::ITankService> tankService,
			SwitchLevelCallbackFunction switchLevelCallback) : BaseLevel(sceneManager, guiEnvironment, functionsProcessingAware, switchLevelCallback)
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
					if (event.GUIEvent.Caller->getID() == GO_TO_BATTLE_CONTROL)
					{
						_goToBattle();

						return true;
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
					return false;
				}
			}

			return false;
		}

	private:
		boost::shared_ptr<irr::gui::IGUIListBox> _tanksList;

		boost::shared_ptr<BLL::Services::User::IUserService> _userService;
		boost::shared_ptr<BLL::Services::Tanks::ITankService> _tankService;

		void _createUi()
		{
			std::wstring path = L"Resources/Levels/Garage/GUI/Garage.xml";
			_loadGui(path);

			boost::shared_ptr<irr::gui::IGUIElement> element = _guiEnvironment->getRootGUIElement()->getElementFromId(TANKS_LIST_CONTROL, true);
			_tanksList = boost::static_pointer_cast<irr::gui::IGUIListBox>(element);

			_functionsProcessingAware->addFuctionToQueue(
				ThreadTypes::THREAD_POOL,
				[&]()
				{
					boost::shared_ptr<BLL::Models::DataActionResult<BLL::Models::User::Info>> userInfo = _userService->getInfo();

					_functionsProcessingAware->addFuctionToQueue(
						ThreadTypes::RENDER_THREAD,
						[&, userInfo]()
						{
							boost::shared_ptr<irr::gui::IGUIElement> element;

							element = _guiEnvironment->getRootGUIElement()->getElementFromId(USER_NAME_CONTROL, true);
							boost::shared_ptr<irr::gui::IGUIStaticText> userNameLabel = boost::static_pointer_cast<irr::gui::IGUIStaticText>(element);
							userNameLabel->setText(userInfo->getData().getName().c_str());

							element = _guiEnvironment->getRootGUIElement()->getElementFromId(MONEY_VALUE_CONTROL, true);
							boost::shared_ptr<irr::gui::IGUIStaticText> moneyLabel = boost::static_pointer_cast<irr::gui::IGUIStaticText>(element);
							moneyLabel->setText(std::to_wstring(userInfo->getData().getMoney()).c_str());
						});
				});

			_functionsProcessingAware->addFuctionToQueue(
				ThreadTypes::THREAD_POOL,
				[&]()
				{
					boost::shared_ptr<BLL::Models::DataActionResult<std::vector<BLL::Models::Tanks::Tank>>> allTank = _tankService->getAll();

					_functionsProcessingAware->addFuctionToQueue(
						ThreadTypes::RENDER_THREAD,
						[&, allTank]()
						{
							for (const BLL::Models::Tanks::Tank tank : allTank->getData())
							{
								_tanksList->addItem(tank.getName().c_str());
							}
						});
				});
		}

		void _createScene()
		{
			std::wstring path = L"Resources/Levels/Garage/Garage.irr";
			_loadScene(path);

			_sceneManager->addCameraSceneNode()->addAnimator(
				boost::make_shared<T10::Levels::Garage::Cameras::GarageCameraAnimator>(irr::core::vector3df(0, 0, 0), 10));

			_sceneManager->addCubeSceneNode(5, 0, -1, {0, 0, 0});
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
			irr::s32 selectedTankIndex = _tanksList->getSelected();
		}
	};
}

#endif