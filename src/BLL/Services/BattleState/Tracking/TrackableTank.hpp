#ifndef TRACKABLE_TANK
#define TRACKABLE_TANK

#include "TrackableObject.h"
#include "ITrackableTank.h"

namespace T10::BLL::Services::BattleState::Tracking {

	class TrackableTank : public TrackableObject, public ITrackableTank {

	};

}