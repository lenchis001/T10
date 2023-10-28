#ifndef BUY_TANK_DIALOG_CONTROLLER
#define BUY_TANK_DIALOG_CONTROLLER

#include "IFunctionsProcessingAware.h"
#include "BLL/Models/Tanks/Tank.hpp"

#include "irrlicht.h"

#include "vector"

#include "boost/function.hpp"

#define BUY_TANK_DIALOG_CONTROL 6
#define BUY_TANK_DIALOG_LIST_CONTROL 8
#define BUY_TANK_DIALOG_ACTION_BUTTON_CONTROL 9

namespace T10::Levels::Garage
{
	class BuyTankDialogController
	{
	public:
		BuyTankDialogController(
			boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
			boost::shared_ptr<irr::gui::IGUIElement> rootGuiElement) {
			_functionsProcessingAware = functionsProcessingAware;
			_rootGuiElement = rootGuiElement;
		}

		void show(boost::shared_ptr<const std::vector<BLL::Models::Tanks::Tank>> allTanks, boost::function<void()> onHidden) {
			_onHidden = onHidden;
			_allTanks = allTanks;

			boost::shared_ptr<irr::gui::IGUIElement> element = _rootGuiElement->getElementFromId(BUY_TANK_DIALOG_LIST_CONTROL, true);
			_availableTanksList = boost::static_pointer_cast<irr::gui::IGUIListBox>(element);

			element = _rootGuiElement->getElementFromId(BUY_TANK_DIALOG_ACTION_BUTTON_CONTROL, true);
			_actionButton = boost::static_pointer_cast<irr::gui::IGUIButton>(element);

			_functionsProcessingAware->addFuctionToQueue(
				ThreadTypes::THREAD_POOL,
				[&]()
				{
					for (const BLL::Models::Tanks::Tank& tank : *_allTanks)
					{
						_availableTanksList->addItem(tank.getName().c_str());
					}
				});
		}

		bool OnEvent(const irr::SEvent &event) {
			if (event.EventType == irr::EEVENT_TYPE::EET_GUI_EVENT)
			{
				switch (event.GUIEvent.EventType)
				{
					// case irr::gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED:
					// {
					// 	boost::shared_ptr<irr::gui::IGUIButton> button = boost::static_pointer_cast<irr::gui::IGUIButton>(event.GUIEvent.Caller);

					// 	switch (event.GUIEvent.Caller->getID())
					// 	{
					// 	case GO_TO_BATTLE_CONTROL:
					// 		_goToBattle();
					// 		return true;

					// 	case BUY_TANK_CONTROL:
					// 		_showTanksBuyDialog();
					// 		return true;

					// 	default:
					// 		break;
					// 	}

					// 	break;
					// }
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
		boost::shared_ptr<irr::gui::IGUIElement> _rootGuiElement;
		boost::shared_ptr<irr::gui::IGUIListBox> _availableTanksList;
		boost::shared_ptr<irr::gui::IGUIButton> _actionButton;

		boost::shared_ptr<const std::vector<BLL::Models::Tanks::Tank>> _allTanks;

		boost::function<void()> _onHidden;

		void _onTankSelected() {
			auto selectedTankIndex = _availableTanksList->getSelected();

			if (selectedTankIndex != -1)
			{
				auto& selectedTank = (*_allTanks)[selectedTankIndex];
			}
		}
	};
}

#endif // BUY_TANK_DIALOG_CONTROLLER