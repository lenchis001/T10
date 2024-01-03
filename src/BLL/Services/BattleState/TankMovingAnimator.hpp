#ifndef TANK_MOVING_ANIMATOR
#define TANK_MOVING_ANIMATOR

#include "irrlicht.h"

#include "Levels/Cameras/ICameraAnimatorDelegate.h"

namespace T10::BLL::Services::BattleState
{
	class TankMovingAnimator : public irr::scene::ISceneNodeAnimator
	{
	public:
		TankMovingAnimator(float movingSpeed, float rotationSpeed)
		{
			_moveX = false;
			_moveY = false;

			_movingSpeed = movingSpeed;
			_rotationSpeed = rotationSpeed;

			_previousAnimationTime = 0;
		}

		void move(int moveX, int moveY)
		{
			_moveX = moveX;
			_moveY = moveY;
		}

		void animateNode(boost::shared_ptr<irr::scene::ISceneNode> node, irr::u32 timeMs) override
		{
			auto timeDelta = timeMs - _previousAnimationTime;
			_previousAnimationTime = timeMs;

			_rotateNode(node, _moveY * _rotationSpeed * timeDelta);
			_moveNode(node, _moveX * _movingSpeed * timeDelta);
		}

		boost::shared_ptr<ISceneNodeAnimator> createClone(boost::shared_ptr<irr::scene::ISceneNode> node,
			boost::shared_ptr<irr::scene::ISceneManager> newManager = 0) {
			return nullptr;
		}
	private:
		int _moveX, _moveY;
		float _movingSpeed, _rotationSpeed;
		irr::u32 _previousAnimationTime;

		void _rotateNode(boost::shared_ptr<irr::scene::ISceneNode> node, irr::f32 value) const
		{
			auto rotation = node->getRotation();

			rotation.Y += value;

			node->setRotation(rotation);
		}

		void _moveNode(boost::shared_ptr<irr::scene::ISceneNode> node, irr::f32 value) const
		{
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

#endif // TANK_MOVING_ANIMATOR