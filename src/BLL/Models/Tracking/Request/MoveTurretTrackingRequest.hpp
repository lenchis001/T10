#ifndef MOVE_TURRET_TRACKING_REQUEST
#define MOVE_TURRET_TRACKING_REQUEST

#include "ITrackingRequest.hpp"

#include "irrlicht.h"

namespace T10::BLL::Models::Tracking::Request {

	class MoveTurretTrackingRequest : public ITrackingRequest {
	public:
		MoveTurretTrackingRequest(const irr::core::vector3df& value) {
			_value = value;
		}

		std::string toJson() const override {
			return "{"
						"\"name\":\"moveTurret\","
						"\"value\": { "
							"\"x\":" + std::to_string(_value.X) + ","
							"\"y\":" + std::to_string(_value.Y) + ","
							"\"z\":" + std::to_string(_value.Z) + ","
						"}"
					"}";
		}
	private:
		irr::core::vector3df _value;
	};

}

#endif // MOVE_TURRET_TRACKING_REQUEST