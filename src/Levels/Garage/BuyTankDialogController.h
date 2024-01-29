#ifndef BUY_TANK_DIALOG_CONTROLLER
#define BUY_TANK_DIALOG_CONTROLLER

#include "IFunctionsProcessingAware.h"
#include "BLL/Models/Tanks/Tank.hpp"
#include "BLL/Models/TankAssignments/TankAssignment.hpp"
#include "BLL/Services/TankAssignment/ITankAssignmentService.h"

#include "irrlicht.h"

#include "vector"

#include "boost/function.hpp"
#include "boost/shared_ptr.hpp"

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
			boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment);

		void show(boost::shared_ptr<const std::vector<BLL::Models::Tanks::Tank>> allTanks, boost::function<void()> onHidden);
		bool OnEvent(const irr::SEvent& event);

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

		void _onTankSelected();
		bool isMyTank(int tankId);
		void _doAction();
		void _updateTankAssignmentState();
	};
}

#endif // BUY_TANK_DIALOG_CONTROLLER