#ifndef IMESSAGE_HANDLER_FACTORY
#define IMESSAGE_HANDLER_FACTORY

#include "Handlers/IMessageHandler.h"

#include "boost/smart_ptr.hpp"

#include "string"

namespace T10::BLL::Services::BattleState::Tracking::MessageHandling {

	class IMessageHandlerFactory {
	public:
		virtual boost::shared_ptr<Handlers::IMessageHandler> getHandler(const std::string& messageName) = 0;

		virtual void addHandler(const std::string& messageName, boost::shared_ptr<Handlers::IMessageHandler> handler) = 0;
	};

}

#endif // IMESSAGE_HANDLER_FACTORY