#ifndef CURRENT_PLAYER_TANK_MOVING_ANIMATOR
#define CURRENT_PLAYER_TANK_MOVING_ANIMATOR

#include "TankMovingAnimator.hpp"

namespace T10::Levels::Battle::Tank {
	class CurrentPlayerTankMovingAnimator : public TankMovingAnimator {
	public:
		CurrentPlayerTankMovingAnimator(boost::shared_ptr<irr::scene::ISceneNode> tankBody, float movingSpeed, float rotationSpeed) {
			_moveForward = false;
			_moveBackward = false;
			_rotateLeft = false;
			_rotateRight = false;

			_movingSpeed = movingSpeed;
			_rotationSpeed = rotationSpeed;

			_tankBody = tankBody;

			_previousAnimationTime = 0;
		}

		virtual void animateNode(irr::u32 timeMs) {
			auto timeDelta = timeMs - _previousAnimationTime;
			_previousAnimationTime = timeMs;

			if (_rotateLeft) {
				_rotateNode(_tankBody, -_rotationSpeed * timeDelta);
			}
			else if (_rotateRight) {
				_rotateNode(_tankBody, _rotationSpeed * timeDelta);
			}

			if (_moveForward) {
				_moveNode(_tankBody, _movingSpeed * timeDelta);
			}
			else if (_moveBackward) {
				_moveNode(_tankBody, -_movingSpeed * timeDelta);
			}
		}

		virtual bool OnEvent(const irr::SEvent& event)
		{
			if (event.EventType == irr::EEVENT_TYPE::EET_KEY_INPUT_EVENT) {
				switch (event.KeyInput.Key)
				{
				case irr::EKEY_CODE::KEY_KEY_W:
					_moveForward = event.KeyInput.PressedDown;
					return true;
				case irr::EKEY_CODE::KEY_KEY_S:
					_moveBackward = event.KeyInput.PressedDown;
					return true;
				case irr::EKEY_CODE::KEY_KEY_A:
					_rotateLeft = event.KeyInput.PressedDown;
					return true;
				case irr::EKEY_CODE::KEY_KEY_D:
					_rotateRight = event.KeyInput.PressedDown;
					return true;
				default:
					break;
				}
			}

			return false;
		}
	private:
		bool _moveForward, _moveBackward, _rotateLeft, _rotateRight;
		boost::shared_ptr<irr::scene::ISceneNode> _tankBody;
		float _movingSpeed, _rotationSpeed;
		irr::u32 _previousAnimationTime;

		void _rotateNode(boost::shared_ptr<irr::scene::ISceneNode> node, irr::f32 value) const {
			auto rotation = node->getRotation();

			rotation.Y += value;

			node->setRotation(rotation);
		}

		void _moveNode(boost::shared_ptr<irr::scene::ISceneNode> node, irr::f32 value) const {
			auto position = node->getPosition();
			const auto& rotation = node->getRotation();

			auto index = (rotation.Y * -1) / (180 / irr::core::PI);
			
			// sin of PI/2 is 1
			position.X += value /** sin(irr::core::HALF_PI)*/ * cos(index);
			position.Z += value /** sin(irr::core::HALF_PI)*/ * sin(index);

			node->setPosition(position);
		}
	};
} // T10::Levels::Battle::Tank

#endif // CURRENT_PLAYER_TANK_MOVING_ANIMATOR