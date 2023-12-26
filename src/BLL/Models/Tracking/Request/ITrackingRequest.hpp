#ifndef ITRACKING_REQUEST_BASE
#define ITRACKING_REQUEST_BASE

namespace T10::BLL::Models::Tracking::Request {
	class ITrackingRequest {
	public:
		virtual std::string toJson() const = 0;
	};
}

#endif // ITRACKING_REQUEST_BASE