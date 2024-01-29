#include "CorrectTankStateMessageHandler.h"

using namespace T10::BLL::Services::BattleState::Tracking::MessageHandling::Handlers;

CorrectTankStateMessageHandler::CorrectTankStateMessageHandler(boost::shared_ptr<irr::scene::ISceneManager> sceneManager) {
	_sceneManager = sceneManager;
}

void CorrectTankStateMessageHandler::handle(const boost::json::object& messageBody) {
	auto id = messageBody.at("id").as_int64();
	auto position = _parseVector(messageBody.at("bodyPosition").as_object());
	auto rotation = _parseVector(messageBody.at("bodyRotation").as_object());
	auto moveX = messageBody.at("moveX").as_int64();
	auto moveY = messageBody.at("moveY").as_int64();
	auto highPrecision = messageBody.at("highPrecision").as_bool();
	boost::shared_ptr<irr::scene::ISceneNode> targetObject = _sceneManager->getSceneNodeFromId(id);
	if (targetObject) {
		auto tankMovingAnimator = boost::dynamic_pointer_cast<TankMovingAnimator>(_getTankMovingAnimator(targetObject));
		if (tankMovingAnimator) {
			tankMovingAnimator->move(moveX, moveY);
		}
		// todo: add logs
	}
	else {
		// todo: add logs
	}
}

boost::shared_ptr<irr::scene::ISceneNodeAnimator> CorrectTankStateMessageHandler::_getTankMovingAnimator(boost::shared_ptr<irr::scene::ISceneNode> sceneNode) {
	auto& animators = sceneNode->getAnimators();
	auto animatorIterator = std::find_if(animators.begin(), animators.end(), [](auto& animator) {
		return typeid(*animator) == typeid(TankMovingAnimator);
		});
	return animatorIterator != animators.end() ? *animatorIterator : nullptr;
}

void CorrectTankStateMessageHandler::_applyPosition(const irr::core::vector3df& value, boost::shared_ptr<irr::scene::ISceneNode> node, bool highPrecision) {
	auto& currentPosition = node->getPosition();
	if (!currentPosition.equals(value, highPrecision ? irr::core::ROUNDING_ERROR_f32 : POSITION_TOLERANCE)) {
		node->setPosition(value);
	}
}

void CorrectTankStateMessageHandler::_applyRotation(const irr::core::vector3df& value, boost::shared_ptr<irr::scene::ISceneNode> node, bool highPrecision) {
	auto& currentPosition = node->getRotation();
	if (!currentPosition.equals(value, highPrecision ? irr::core::ROUNDING_ERROR_f32 : ROTATION_TOLERANCE)) {
		node->setRotation(value);
	}
}