#ifndef TANK_MOVING_ANIMATOR_H
#define TANK_MOVING_ANIMATOR_H

#include "irrlicht.h"
#include "Levels/Cameras/ICameraAnimatorDelegate.h"

namespace T10::BLL::Services::BattleState
{
    class TankMovingAnimator : public irr::scene::ISceneNodeAnimator
    {
    public:
        TankMovingAnimator(float movingSpeed, float rotationSpeed);
        void move(int moveX, int moveY);
        void animateNode(boost::shared_ptr<irr::scene::ISceneNode> node, irr::u32 timeMs) override;
        boost::shared_ptr<ISceneNodeAnimator> createClone(boost::shared_ptr<irr::scene::ISceneNode> node,
            boost::shared_ptr<irr::scene::ISceneManager> newManager = 0);

    private:
        void _rotateNode(boost::shared_ptr<irr::scene::ISceneNode> node, irr::f32 value) const;
        void _moveNode(boost::shared_ptr<irr::scene::ISceneNode> node, irr::f32 value) const;

        int _moveX, _moveY;
        float _movingSpeed, _rotationSpeed;
        irr::u32 _previousAnimationTime;
    };
} // T10::Levels::Battle::Tank

#endif // TANK_MOVING_ANIMATOR_H