#ifndef MESSAGE_HANDLER_FACTORY_H
#define MESSAGE_HANDLER_FACTORY_H

#include "IMessageHandlerFactory.h"
#include "string"
#include "map"

namespace T10::BLL::Services::BattleState::Tracking::MessageHandling {

	class MessageHandlerFactory : public IMessageHandlerFactory {
	public:
		boost::shared_ptr<Handlers::IMessageHandler> getHandler(const std::string& messageName) override;
		void addHandler(const std::string& messageName, boost::shared_ptr<Handlers::IMessageHandler> handler) override;
		void clear();

	private:
		std::map<std::string, boost::shared_ptr<Handlers::IMessageHandler>> _handlers;
	};

}

#endif // MESSAGE_HANDLER_FACTORY_H