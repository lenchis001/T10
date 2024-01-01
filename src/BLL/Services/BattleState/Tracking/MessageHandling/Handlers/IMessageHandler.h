#ifndef IMESSAGE_HANDLER
#define IMESSAGE_HANDLER

#include "string"

#include "boost/json.hpp"

namespace T10::BLL::Services::BattleState::Tracking::MessageHandling::Handlers {

	class IMessageHandler {
	public:
		virtual void handle(const boost::json::object& messageBody) = 0;
	};

}

#endif // IMESSAGE_HANDLER