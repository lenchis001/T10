#include "TankMovingAnimator.h"

using namespace T10::BLL::Services::BattleState;
using namespace irr::scene;

TankMovingAnimator::TankMovingAnimator(float movingSpeed, float rotationSpeed)
{
    _moveX = false;
    _moveY = false;

    _movingSpeed = movingSpeed;
    _rotationSpeed = rotationSpeed;

    _previousAnimationTime = 0;
}

void TankMovingAnimator::move(int moveX, int moveY)
{
    _moveX = moveX;
    _moveY = moveY;
}

void TankMovingAnimator::animateNode(boost::shared_ptr<irr::scene::ISceneNode> node, irr::u32 timeMs)
{
    auto timeDelta = timeMs - _previousAnimationTime;
    _previousAnimationTime = timeMs;

    _rotateNode(node, _moveY * _rotationSpeed * timeDelta);
    _moveNode(node, _moveX * _movingSpeed * timeDelta);
}

boost::shared_ptr<ISceneNodeAnimator> TankMovingAnimator::createClone(boost::shared_ptr<irr::scene::ISceneNode> node,
    boost::shared_ptr<irr::scene::ISceneManager> newManager)
{
    return nullptr;
}

void TankMovingAnimator::_rotateNode(boost::shared_ptr<irr::scene::ISceneNode> node, irr::f32 value) const
{
    auto rotation = node->getRotation();

    rotation.Y += value;

    node->setRotation(rotation);
}

void TankMovingAnimator::_moveNode(boost::shared_ptr<irr::scene::ISceneNode> node, irr::f32 value) const
{
    auto position = node->getPosition();
    const auto& rotation = node->getRotation();

    auto index = (rotation.Y * -1) / (180 / irr::core::PI);

    // sin of PI/2 is 1
    position.X += value * cos(index);
    position.Z += value * sin(index);

    node->setPosition(position);
}