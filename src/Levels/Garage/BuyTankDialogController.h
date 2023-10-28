#ifndef BUY_TANK_DIALOG_CONTROLLER
#define BUY_TANK_DIALOG_CONTROLLER

#include "IFunctionsProcessingAware.h"

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
			boost::shared_ptr<irr::gui::IGUIElement> rootGuiElement);

		void show(boost::shared_ptr<const vector<BLL::Models::Tanks::Tank>> allTanks, boost::function<void()> onHidden);

		bool OnEvent(const irr::SEvent &event);

	private:
		boost::shared_ptr<IFunctionsProcessingAware> _functionsProcessingAware;
		boost::shared_ptr<irr::gui::IGUIElement> _rootGuiElement;
		boost::shared_ptr<irr::gui::IGUIListBox> _availableTanksList;
		boost::shared_ptr<irr::gui::IGUIButton> _actionButton;

		boost::shared_ptr<const vector<BLL::Models::Tanks::Tank>> _allTanks;

		boost::function<void()> _onHidden;

		void _onTankSelected();
	};
}

#endif // BUY_TANK_DIALOG_CONTROLLER