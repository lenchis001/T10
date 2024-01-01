#ifndef MESSAGE_HANDLER_BASE
#define MESSAGE_HANDLER_BASE

#include "IMessageHandler.h"

#include "irrlicht.h"

namespace T10::BLL::Services::BattleState::Tracking::MessageHandling::Handlers {

	class MessageHandlerBase : public IMessageHandler {
	protected:
		irr::core::vector3df _parseVector(const boost::json::object& value) {
			auto x = value.at("x").as_double();
			auto y = value.at("y").as_double();
			auto z = value.at("z").as_double();

			return irr::core::vector3df(x,y,z);
		}
	};

}

#endif // MESSAGE_HANDLER_BASE