#ifndef ITRACKABLE_TANK
#define ITRACKABLE_TANK

#include "ITrackableObject.h"

namespace T10::BLL::Services::BattleState::Tracking {

	class ITrackableTank : public ITrackableObject {
	public:
		virtual void setHealthPoints(int value) const = 0;

		virtual void setTurretRotation(const irr::core::vector3df& value) = 0;
	};

}

#endif // ITRACKABLE_TANK