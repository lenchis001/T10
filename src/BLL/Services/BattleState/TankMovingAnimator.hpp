#ifndef TANK_MOVING_ANIMATOR
#define TANK_MOVING_ANIMATOR

#include "irrlicht.h"

#include "Levels/Cameras/ICameraAnimatorDelegate.h"

namespace T10::BLL::Services::BattleState
{
	class TankMovingAnimator : public Cameras::ICameraAnimatorDelegate
	{
	public:
		TankMovingAnimator(boost::shared_ptr<irr::scene::ISceneNode> tankBody, float movingSpeed, float rotationSpeed)
		{
			_moveX = false;
			_moveY = false;

			_movingSpeed = movingSpeed;
			_rotationSpeed = rotationSpeed;

			_tankBody = tankBody;

			_previousAnimationTime = 0;
		}

		void move(int moveX, int moveY)
		{
			_moveX = moveX;
			_moveY = moveY;
		}

		virtual void animateNode(irr::u32 timeMs)
		{
			auto timeDelta = timeMs - _previousAnimationTime;
			_previousAnimationTime = timeMs;

			_rotateNode(_tankBody, _moveY * _rotationSpeed * timeDelta);
			_moveNode(_tankBody, _moveX * _movingSpeed * timeDelta);
		}

		virtual bool OnEvent(const irr::SEvent& event)
		{
			return false;
		}

	private:
		int _moveX, _moveY;
		boost::shared_ptr<irr::scene::ISceneNode> _tankBody;
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