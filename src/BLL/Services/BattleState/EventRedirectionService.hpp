#ifndef EVENT_REDIRECTION_SERVICE
#define EVENT_REDIRECTION_SERVICE

#include "irrlicht.h"

#include "BLL/Services/BattleState/IBattleStateSynchronizationService.h"

namespace T10::BLL::Services::BattleState {

	class EventRedirectionService {
	public:
		EventRedirectionService(boost::shared_ptr<BLL::Services::BattleState::IBattleStateSynchronizationService> battleStateSynchronizationService) {
			_battleStateSynchronizationService = battleStateSynchronizationService;

			_moveX = _moveY = _lastReportedMoveX = _lastReportedMoveY = 0;
		}

		bool OnEvent(const irr::SEvent::SKeyInput& eventData) {
			switch (eventData.Key)
			{
			case irr::EKEY_CODE::KEY_KEY_W:
				_moveX = eventData.PressedDown;
				_reportMoveX();
				return true;
			case irr::EKEY_CODE::KEY_KEY_S:
				_moveX = -eventData.PressedDown;
				_reportMoveX();
				return true;
			case irr::EKEY_CODE::KEY_KEY_A:
				_moveY = -eventData.PressedDown;
				_reportMoveY();
				return true;
			case irr::EKEY_CODE::KEY_KEY_D:
				_moveY = eventData.PressedDown;
				_reportMoveY();
				return true;
			default:
				break;
			}

			return false;
		}
	private:
		int _moveX, _moveY, _lastReportedMoveX, _lastReportedMoveY;

		void _reportMoveX() {
			if (_lastReportedMoveX != _moveX) {
				_battleStateSynchronizationService->moveBody(_moveX, _moveY);
				_lastReportedMoveX = _moveX;
			}
		}

		void _reportMoveY() {
			if (_lastReportedMoveY != _moveY) {
				_battleStateSynchronizationService->moveBody(_moveX, _moveY);
				_lastReportedMoveY = _moveY;
			}
		}

		boost::shared_ptr<BLL::Services::BattleState::IBattleStateSynchronizationService> _battleStateSynchronizationService;
	};
}

#endif // EVENT_REDIRECTION_SERVICE