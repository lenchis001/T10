#include "CorrectObjectStateMessageHandler.h"

using namespace T10::BLL::Services::BattleState::Tracking::MessageHandling::Handlers;

CorrectObjectStateMessageHandler::CorrectObjectStateMessageHandler(boost::shared_ptr<irr::scene::ISceneManager> sceneManager) {
	_sceneManager = sceneManager;
}

void CorrectObjectStateMessageHandler::handle(const boost::json::object& messageBody) {
	auto id = messageBody.at("id").as_int64();
	auto position = _parseVector(messageBody.at("position").as_object());
	auto rotation = _parseVector(messageBody.at("rotation").as_object());

	auto targetObject = _sceneManager->getSceneNodeFromId(id);

	if (targetObject) {
		targetObject->setPosition(position);
		targetObject->setRotation(rotation);
	}
	else {
		// todo: add logs
	}
}