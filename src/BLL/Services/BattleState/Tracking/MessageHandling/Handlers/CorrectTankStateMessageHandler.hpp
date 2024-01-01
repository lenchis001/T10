#ifndef CORRECT_TANK_STATE_MESSAGE_HANDLER
#define CORRECT_TANK_STATE_MESSAGE_HANDLER

#include "MessageHandlerBase.hpp"
#include "BLL/Services/BattleState/TankMovingAnimator.hpp"

#define POSITION_TOLERANCE 3.0F
#define ROTATION_TOLERANCE 3.0F

namespace T10::BLL::Services::BattleState::Tracking::MessageHandling::Handlers {

	class CorrectTankStateMessageHandler : public MessageHandlerBase {
	public:
		CorrectTankStateMessageHandler(boost::shared_ptr<irr::scene::ISceneManager> sceneManager) {
			_sceneManager = sceneManager;
		}

		void handle(const boost::json::object& messageBody) override {
			auto id = messageBody.at("id").as_int64();
			auto position = _parseVector(messageBody.at("bodyPosition").as_object());
			auto rotation = _parseVector(messageBody.at("bodyRotation").as_object());
			auto moveX = messageBody.at("moveX").as_int64();
			auto moveY = messageBody.at("moveY").as_int64();

			auto highPrecision = messageBody.at("highPrecision").as_bool();

			boost::shared_ptr<irr::scene::ISceneNode> targetObject = _sceneManager->getSceneNodeFromId(id);

			if (targetObject) {
				_applyPosition(position, targetObject, highPrecision);
				_applyRotation(rotation, targetObject, highPrecision);

				auto tankMovingAnimator = boost::dynamic_pointer_cast<TankMovingAnimator>(_getTankMovingAnimator(targetObject));

				if (tankMovingAnimator) {
					tankMovingAnimator->move(moveX, moveY);
				}
				else {
					// todo: add logs
				}
			}
			else {
				// todo: add logs
			}
		}
	private:
		boost::shared_ptr<irr::scene::ISceneManager> _sceneManager;

		static boost::shared_ptr<irr::scene::ISceneNodeAnimator> _getTankMovingAnimator(boost::shared_ptr<irr::scene::ISceneNode> sceneNode) {
			auto& animators = sceneNode->getAnimators();

			auto animatorIterator = std::find_if(animators.begin(), animators.end(), [](auto& animator) {
				return false;
			});

			return animatorIterator != animators.end() ? *animatorIterator : nullptr;
		}

		static void _applyPosition(const irr::core::vector3df& value, boost::shared_ptr<irr::scene::ISceneNode> node, bool highPrecision) {
			auto& currentPosition = node->getPosition();

			if (!currentPosition.equals(value, highPrecision ? irr::core::ROUNDING_ERROR_f32 : POSITION_TOLERANCE)) {
				node->setPosition(value);
			}
		}

		static void _applyRotation(const irr::core::vector3df& value, boost::shared_ptr<irr::scene::ISceneNode> node, bool highPrecision) {
			auto& currentPosition = node->getRotation();

			if (!currentPosition.equals(value, highPrecision ? irr::core::ROUNDING_ERROR_f32 : ROTATION_TOLERANCE)) {
				node->setRotation(value);
			}
		}
	};

}

#endif // CORRECT_TANK_STATE_MESSAGE_HANDLER