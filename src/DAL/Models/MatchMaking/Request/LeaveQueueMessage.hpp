#ifndef LEAVE_QUEUE_DAL_MESSAGE
#define LEAVE_QUEUE_DAL_MESSAGE

#include "BaseMessage.hpp"

namespace T10::DAL::Models::MatchMaking::Request {

	class LeaveQueueMessage: public BaseMessage  {
	public:
		boost::json::object toJson() const override {
			return _toJson("leaveQueue", boost::json::object());
		}
	};

}

#endif // LEAVE_QUEUE_DAL_MESSAGE