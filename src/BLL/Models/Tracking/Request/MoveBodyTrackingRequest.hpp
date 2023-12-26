#ifndef MOVE_BODY_TRACKING_REQUEST
#define MOVE_BODY_TRACKING_REQUEST

#include "ITrackingRequest.hpp"

#include "irrlicht.h"

namespace T10::BLL::Models::Tracking::Request {

	class MoveBodyTrackingRequest : public ITrackingRequest {
	public:
		MoveBodyTrackingRequest(int left, int right) {
			_left = left;
			_right = right;
		}

		std::string toJson() const override {
			return "{"
						"\"name\":\"moveBody\","
						"\"value\": { "
							"\"left\":" + std::to_string(_left) + ","
							"\"right\":" + std::to_string(_right) + ","
						"}"
					"}";
		}
	private:
		int _left, _right;
	};

}

#endif // MOVE_BODY_TRACKING_REQUEST