#ifndef FIRE_TRACKING_REQUEST_BASE
#define FIRE_TRACKING_REQUEST_BASE

#include "ITrackingRequest.hpp"

namespace T10::BLL::Models::Tracking::Request {

	class FireTrackingRequest : public ITrackingRequest {
	public:
		std::string toJson() const override {
			return "{ \"name\":\"fire\" }";
		}
	};

}

#endif // FIRE_TRACKING_REQUEST_BASE