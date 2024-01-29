#ifndef MESSAGE_HANDLER_BASE_H
#define MESSAGE_HANDLER_BASE_H

#include "IMessageHandler.h"
#include "irrlicht.h"

namespace T10::BLL::Services::BattleState::Tracking::MessageHandling::Handlers {

	class MessageHandlerBase : public IMessageHandler {
	protected:
		irr::core::vector3df _parseVector(const boost::json::object& value);
	};

}

#endif // MESSAGE_HANDLER_BASE_H