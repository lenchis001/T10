#ifndef BUY_TANK_DIALOG_CONTROLLER
#define BUY_TANK_DIALOG_CONTROLLER

#include "IFunctionsProcessingAware.h"
#include "BLL/Models/Tanks/Tank.hpp"
#include "BLL/Models/TankAssignments/TankAssignment.hpp"
#include "BLL/Services/TankAssignment/ITankAssignmentService.h"

#include "irrlicht.h"

#include "vector"

#include "boost/function.hpp"

#define BUY_TANK_DIALOG_CONTROL 6
#define BUY_TANK_DIALOG_LIST_CONTROL 8
#define BUY_TANK_DIALOG_ACTION_BUTTON_CONTROL 9
#define BUY_TANK_DIALOG_PRICE_TEXT_CONTROL 10
#define BUY_TANK_DIALOG_NAME_TEXT_CONTROL 11

namespace T10::Levels::Garage
{
	class BuyTankDialogController
	{
	public:
		BuyTankDialogController(
			boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
			boost::shared_ptr<BLL::Services::TankAssignment::ITankAssignmentService> tankAssignmentService,
			boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment) {
			_functionsProcessingAware = functionsProcessingAware;
			_tankAssignmentService = tankAssignmentService;
			_guiEnvironment = guiEnvironment;
		}

		void show(boost::shared_ptr<const std::vector<BLL::Models::Tanks::Tank>> allTanks, boost::function<void()> onHidden) {
			_onHidden = onHidden;
			_allTanks = allTanks;

			_updateTankAssignmentState();

			auto rootGuiElement = _guiEnvironment->getRootGUIElement();

			boost::shared_ptr<irr::gui::IGUIElement> element = rootGuiElement->getElementFromId(BUY_TANK_DIALOG_LIST_CONTROL, true);
			_availableTanksList = boost::static_pointer_cast<irr::gui::IGUIListBox>(element);

			element = rootGuiElement->getElementFromId(BUY_TANK_DIALOG_ACTION_BUTTON_CONTROL, true);
			_actionButton = boost::static_pointer_cast<irr::gui::IGUIButton>(element);

			element = rootGuiElement->getElementFromId(BUY_TANK_DIALOG_PRICE_TEXT_CONTROL, true);
			_priceText = boost::static_pointer_cast<irr::gui::IGUIStaticText>(element);

			element = rootGuiElement->getElementFromId(BUY_TANK_DIALOG_NAME_TEXT_CONTROL, true);
			_nameText = boost::static_pointer_cast<irr::gui::IGUIStaticText>(element);

			for (const BLL::Models::Tanks::Tank& tank : *_allTanks)
			{
				_availableTanksList->addItem(tank.getName().c_str());
			}
		}

		bool OnEvent(const irr::SEvent& event) {
			if (event.EventType == irr::EEVENT_TYPE::EET_GUI_EVENT)
			{
				switch (event.GUIEvent.EventType)
				{
				case irr::gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED:
				{
					boost::shared_ptr<irr::gui::IGUIButton> button = boost::static_pointer_cast<irr::gui::IGUIButton>(event.GUIEvent.Caller);

					switch (event.GUIEvent.Caller->getID())
					{
					case BUY_TANK_DIALOG_ACTION_BUTTON_CONTROL:
						_doAction();
						return true;

					default:
						break;
					}

					break;
				}
				case irr::gui::EGUI_EVENT_TYPE::EGET_LISTBOX_CHANGED:
				{
					if (event.GUIEvent.Caller->getID() == BUY_TANK_DIALOG_LIST_CONTROL)
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
						_onHidden();

						break;
					}

					break;
				}
				default:
					break;
				}
			}

			return false;
		}

	private:
		boost::shared_ptr<IFunctionsProcessingAware> _functionsProcessingAware;
		boost::shared_ptr<irr::gui::IGUIEnvironment> _guiEnvironment;
		boost::shared_ptr<irr::gui::IGUIListBox> _availableTanksList;
		boost::shared_ptr<irr::gui::IGUIButton> _actionButton;
		boost::shared_ptr<irr::gui::IGUIStaticText> _priceText, _nameText;

		boost::shared_ptr<const std::vector<BLL::Models::Tanks::Tank>> _allTanks;
		boost::shared_ptr<std::vector<BLL::Models::TankAssignments::TankAssignment>> _myTanks;
		boost::shared_ptr<BLL::Services::TankAssignment::ITankAssignmentService> _tankAssignmentService;

		boost::function<void()> _onHidden;

		void _onTankSelected() {
			auto selectedTankIndex = _availableTanksList->getSelected();

			if (selectedTankIndex != -1)
			{
				auto& selectedTank = (*_allTanks)[selectedTankIndex];

				_nameText->setText(selectedTank.getName().c_str());
				_priceText->setText(to_wstring(selectedTank.getPrice()).c_str());

				_actionButton->setVisible(true);
				_actionButton->setText(isMyTank(selectedTank.getId()) ? L"Sell" : L"Buy");
			}
		}

		bool isMyTank(int tankId) {
			return std::find_if(_myTanks->begin(), _myTanks->end(), [&](auto t)
				{ return t.getTankId() == tankId; }) != _myTanks->end();
		}

		void _doAction() {
			auto selectedTankIndex = _availableTanksList->getSelected();

			if (selectedTankIndex != -1)
			{
				const auto& selectedTank = (*_allTanks)[selectedTankIndex];

				if (isMyTank(selectedTank.getId())) {
					const auto& tankAssignmentId = find_if(_myTanks->begin(), _myTanks->end(), [&](const auto& ta) {
						return ta.getTankId() == selectedTank.getId();
						})->getId();

						auto bllResult = _tankAssignmentService->sell(tankAssignmentId);

						if (!bllResult->isOk()) {
							_guiEnvironment->addMessageBox(L"Message", L"An error occurred on attempt to sell the tank.");
						}
				}
				else {
					auto bllTankAssignment = BLL::Models::TankAssignments::AddTankAssignment(selectedTank.getId());
					auto bllResult = _tankAssignmentService->buy(bllTankAssignment);

					if (!bllResult->isOk()) {
						_guiEnvironment->addMessageBox(L"Message", L"An error occurred on attempt to buy the tank.");
					}
				}

				_updateTankAssignmentState();
				_onTankSelected();
			}
		}

		void _updateTankAssignmentState() {
			boost::shared_ptr<BLL::Models::DataActionResult<std::vector<BLL::Models::TankAssignments::TankAssignment>>> myTanks = _tankAssignmentService->getMy();
			if (!myTanks->isOk())
			{
				// todo: add an error handling
				exit(1);
			}
			_myTanks = boost::make_shared<std::vector<BLL::Models::TankAssignments::TankAssignment>>(myTanks->getData());
		}
	};
}

#endif // BUY_TANK_DIALOG_CONTROLLER