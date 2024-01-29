#include "MessageHandlerFactory.h"

using namespace T10::BLL::Services::BattleState::Tracking::MessageHandling;

boost::shared_ptr<Handlers::IMessageHandler> MessageHandlerFactory::getHandler(const std::string& messageName) {
	auto handlerIterator = _handlers.find(messageName);

	return handlerIterator == _handlers.end() ? nullptr : handlerIterator->second;
}

void MessageHandlerFactory::addHandler(const std::string& messageName, boost::shared_ptr<Handlers::IMessageHandler> handler) {
	_handlers.insert({ messageName, handler });
}

void MessageHandlerFactory::clear() {
	_handlers.clear();
}