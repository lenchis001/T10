#include "GarageLevel.h"
#include "cameras/GarageCameraAnimator.h"
#include "iostream"

namespace T10
{
#define TANKS_LIST_CONTROL 1
#define GO_TO_BATTLE_CONTROL 2
#define USER_NAME_CONTROL 3
#define MONEY_VALUE_CONTROL 4

	GarageLevel::GarageLevel(
		boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
		boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment,
		boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
		boost::shared_ptr<BLL::Services::User::IUserService> userService,
		boost::shared_ptr<BLL::Services::Tanks::ITankService> tankService,
		SwitchLevelCallbackFunction switchLevelCallback)
		: BaseLevel(sceneManager, guiEnvironment, functionsProcessingAware, switchLevelCallback)
	{
		_userService = userService;
		_tankService = tankService;
	}

	void GarageLevel::onLoadRequested()
	{
		_createUi();
		_createScene();
	}

	void GarageLevel::onUnloadRequested()
	{
	}

	bool GarageLevel::OnEvent(const irr::SEvent &event)
	{
		if (event.EventType == irr::EEVENT_TYPE::EET_GUI_EVENT)
		{
			if (event.GUIEvent.EventType == irr::gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED)
			{
				boost::shared_ptr<irr::gui::IGUIButton> button = boost::static_pointer_cast<irr::gui::IGUIButton>(event.GUIEvent.Caller);
				if (button->getID() == GO_TO_BATTLE_CONTROL)
				{
					_goToBattle();
				}

				return true;
			}
		}

		return false;
	}

	void GarageLevel::_createUi()
	{
		std::wstring path = L"Resources/Levels/Garage/GUI/Garage.xml";
		_loadGui(path);

		boost::shared_ptr<irr::gui::IGUIElement> element = _guiEnvironment->getRootGUIElement()->getElementFromId(TANKS_LIST_CONTROL, true);
		_tanksList = boost::static_pointer_cast<irr::gui::IGUIListBox>(element);

		_functionsProcessingAware->addFuctionToQueue(
			ThreadTypes::THREAD_POOL,
			[&]()
			{
				boost::shared_ptr<BLL::Models::ActionResult<BLL::Models::User::Info>> userInfo = _userService->getInfo();

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
				boost::shared_ptr<BLL::Models::ActionResult<std::vector<BLL::Models::Tanks::Tank>>> allTank = _tankService->getAll();

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

	void GarageLevel::_createScene()
	{
		std::wstring path = L"Resources/Levels/Garage/Garage.irr";
		_loadScene(path);

		_sceneManager->addCameraSceneNode()->addAnimator(
			boost::make_shared<T10::levels::garage::cameras::GarageCameraAnimator>(irr::core::vector3df(0, 2, 0), 10));
	}

	void GarageLevel::_goToBattle()
	{
		irr::s32 selectedTankIndex = _tanksList->getSelected();

		if (selectedTankIndex != -1)
		{
		}
	}
}