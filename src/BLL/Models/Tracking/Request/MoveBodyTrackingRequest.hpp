#ifndef MOVE_BODY_TRACKING_REQUEST
#define MOVE_BODY_TRACKING_REQUEST

#include "ITrackingRequest.hpp"

#include "irrlicht.h"

namespace T10::BLL::Models::Tracking::Request {

	class MoveBodyTrackingRequest : public ITrackingRequest {
	public:
		MoveBodyTrackingRequest(int x, int y) {
			_x = x;
			_y = y;
		}

		std::string toJson() const override {
			return "{"
						"\"name\":\"moveBody\","
						"\"value\": { "
							"\"x\":" + std::to_string(_x) + ","
							"\"y\":" + std::to_string(_y) + ""
						"}"
					"}";
		}
	private:
		int _x, _y;
	};

}

#endif // MOVE_BODY_TRACKING_REQUEST