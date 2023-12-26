#ifndef ITRACKING_REQUEST
#define ITRACKING_REQUEST

namespace T10::BLL::Models::Tracking::Request {
	class ITrackingRequest {
	public:
		virtual std::string toJson() const = 0;
	};
}

#endif // ITRACKING_REQUEST