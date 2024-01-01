#ifndef MESSAGE_HANDLER_FACTORY
#define MESSAGE_HANDLER_FACTORY

#include "IMessageHandlerFactory.h"

#include "string"
#include "map"

namespace T10::BLL::Services::BattleState::Tracking::MessageHandling {

	class MessageHandlerFactory : public IMessageHandlerFactory {
	public:
		boost::shared_ptr<Handlers::IMessageHandler> getHandler(const std::string& messageName) {
			auto handlerIterator = _handlers.find(messageName);

			return handlerIterator == _handlers.end() ? nullptr : handlerIterator->second;
		}

		void addHandler(const std::string& messageName, boost::shared_ptr<Handlers::IMessageHandler> handler) override {
			_handlers.insert({ messageName, handler });
		}

		void clear() {
			_handlers.clear();
		}

	private:
		std::map<std::string, boost::shared_ptr<Handlers::IMessageHandler>> _handlers;
	};

}

#endif // MESSAGE_HANDLER_FACTORY