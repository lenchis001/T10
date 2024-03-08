#include "StartBattleDialogController.h"

#include "boost/bind.hpp"

using namespace T10::Levels::Garage;

StartBattleDialogController::StartBattleDialogController(
	boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
	boost::shared_ptr<BLL::Services::MatchMaking::IMatchMakingService> matchMakingService,
	boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment) {
	_matchMakingService = matchMakingService;
}

void StartBattleDialogController::show(int tankId, boost::function<void()> onHidden) {
	_onHidden = onHidden;

	_matchMakingService->setBattleStartedHandler(boost::bind(&StartBattleDialogController::_onBattleStarted, this));
	_matchMakingService->setQueueLeftHandler(boost::bind(&StartBattleDialogController::_onBattleLeft, this));
	_matchMakingService->joinQueue(tankId);
}

bool StartBattleDialogController::OnEvent(const irr::SEvent& event) {
	if (event.EventType == irr::EEVENT_TYPE::EET_GUI_EVENT)
	{
		switch (event.GUIEvent.EventType)
		{
		case irr::gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED:
		{
			boost::shared_ptr<irr::gui::IGUIButton> button = boost::static_pointer_cast<irr::gui::IGUIButton>(event.GUIEvent.Caller);

			switch (event.GUIEvent.Caller->getID())
			{
			default:
				break;
			}

			break;
		}
		case irr::gui::EGUI_EVENT_TYPE::EGET_ELEMENT_CLOSED:
		{
			if (event.GUIEvent.Caller->getID() == START_BATTLE_DIALOG_CONTROL)
			{
				_matchMakingService->leaveQueue();
				return true;
			}

			break;
		}
		default:
			break;
		}
	}

	return false;
}

void StartBattleDialogController::_onBattleStarted() {

}

void StartBattleDialogController::_onBattleLeft() {
	_onHidden();
}