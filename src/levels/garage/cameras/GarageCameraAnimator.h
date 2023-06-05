#include "irrlicht.h"

namespace T10::levels::garage::cameras
{
  class GarageCameraAnimator : public irr::scene::ISceneNodeAnimator
  {
  public:
    GarageCameraAnimator(
        irr::core::vector3df target,
        float distance = 10,
        float minTheta = 0.6F,
        float maxTheta = irr::core::HALF_PI - 0.2,
        int sensitivity = 300);

    bool OnEvent(const irr::SEvent &event) override;

    boost::shared_ptr<irr::scene::ISceneNodeAnimator> createClone(boost::shared_ptr<irr::scene::ISceneNode> node,
                                                                  boost::shared_ptr<irr::scene::ISceneManager> newManager = 0) override;

    void animateNode(boost::shared_ptr<irr::scene::ISceneNode> node, irr::u32 timeMs) override;

    bool isEventReceiverEnabled() const override;

  private:
    void _recalculatePosition();

    void _processMouseEvent(int x, int y, bool isLeftButtonPressed);

    void _calculateInclination(float xDelta, float yDelta);

    int _sensitivity;
    irr::core::vector2di _previousMousePoint;
    irr::core::vector3df _target, _position;
    float _distance, _phi, _theta, _minTheta, _maxTheta;
    bool _isTargetUpdated, _isCameraUpdateRequired;
  };
}