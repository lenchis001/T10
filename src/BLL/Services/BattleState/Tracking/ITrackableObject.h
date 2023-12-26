#ifndef ITRACKABLE_OBJECT
#define ITRACKABLE_OBJECT

#include "irrlicht.h"

namespace T10::BLL::Services::BattleState::Tracking {

	class ITrackableObject {
		virtual const irr::core::vector3df& getPosition() const = 0;
		virtual void setPosition(const irr::core::vector3df& value) = 0;

		virtual const irr::core::vector3df& getRotation() const = 0;
		virtual void setRotation(const irr::core::vector3df& value) = 0;

		virtual int getId() const = 0;

		virtual bool isDestroyed() const = 0;
	};

}

#endif // ITRACKABLE_OBJECT