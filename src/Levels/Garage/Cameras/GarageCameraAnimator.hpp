#ifndef GARAGE_CAMERA_ANIMATOR
#define GARAGE_CAMERA_ANIMATOR

#include "irrlicht.h"

namespace T10::Levels::Garage::Cameras
{
  const float TWO_PI = irr::core::PI * 2;

  class GarageCameraAnimator : public irr::scene::ISceneNodeAnimator
  {
  public:
    GarageCameraAnimator(
        irr::core::vector3df target,
        float distance = 10,
        float minTheta = 0.6F,
        float maxTheta = irr::core::HALF_PI - 0.2,
        int sensitivity = 300,
        float phi = 0.85,
        float theta = 1.2)
    {
      _target = target;
      _distance = distance;
      _minTheta = minTheta;
      _maxTheta = maxTheta;
      _sensitivity = sensitivity;

      assert(_minTheta >= 0);
      assert(maxTheta <= irr::core::PI);
      assert(_sensitivity > 0);

      _phi = phi;
      _theta = theta;
      _recalculatePosition();
      _isCameraUpdateRequired = true;

      // It means that start point is not set yet
      _previousMousePoint.X = -1;
    }

    bool OnEvent(const irr::SEvent &event) override
    {
      if (event.EventType == irr::EEVENT_TYPE::EET_MOUSE_INPUT_EVENT)
      {
        _processMouseEvent(event.MouseInput.X, event.MouseInput.Y, event.MouseInput.isLeftPressed());
      }

      return ISceneNodeAnimator::OnEvent(event);
    }

    boost::shared_ptr<irr::scene::ISceneNodeAnimator> createClone(boost::shared_ptr<irr::scene::ISceneNode> node,
                                                                  boost::shared_ptr<irr::scene::ISceneManager> newManager = 0) override
    {
      return boost::make_shared<GarageCameraAnimator>(_target, _distance);
    }

    void animateNode(boost::shared_ptr<irr::scene::ISceneNode> node, irr::u32 timeMs) override
    {
      if (!_isCameraUpdateRequired)
      {
        // no updates requires, don't do useless job
        return;
      }

      boost::shared_ptr<irr::scene::ICameraSceneNode> camera = boost::static_pointer_cast<irr::scene::ICameraSceneNode>(node);

      if (!_isTargetUpdated)
      {
        camera->setTarget(this->_target);
        _isTargetUpdated = true;
      }

      camera->setPosition(_position);

      _isCameraUpdateRequired = false;
    }

    bool isEventReceiverEnabled() const override
    {
      return true;
    }

  private:
    void _recalculatePosition()
    {
      _position.X = _distance * sin(_theta) * cos(_phi);
      _position.Y = _distance * cos(_theta);
      _position.Z = _distance * sin(_theta) * sin(_phi);
    }

    void _processMouseEvent(int x, int y, bool isLeftButtonPressed)
    {
      if (isLeftButtonPressed)
      {
        if (_previousMousePoint.X < 0)
        {
          _previousMousePoint.X = x;
          _previousMousePoint.Y = y;

          // it's the first event for this manipolation
          // it's the start point for next calculations
          return;
        }

        int xDelta = _previousMousePoint.X - x;
        int yDelta = _previousMousePoint.Y - y;
        _calculateInclination(xDelta, yDelta);

        _recalculatePosition();

        _previousMousePoint.X = x;
        _previousMousePoint.Y = y;
        _isCameraUpdateRequired = true;
      }
      else
      {
        _previousMousePoint.X = -1;
        _isCameraUpdateRequired = false;
      }
    }

    void _calculateInclination(float xDelta, float yDelta)
    {
      _phi += xDelta / _sensitivity;
      _theta += yDelta / _sensitivity;

      if (_phi < 0)
      {
        _phi = TWO_PI - fmod(_phi, TWO_PI);
      }
      else if (_phi > TWO_PI)
      {
        _phi = fmod(_phi, TWO_PI);
      }

      if (_theta < _minTheta)
      {
        _theta = _minTheta;
      }
      else if (_theta > _maxTheta)
      {
        _theta = _maxTheta;
      }
    }

    int _sensitivity;
    irr::core::vector2di _previousMousePoint;
    irr::core::vector3df _target, _position;
    float _distance, _phi, _theta, _minTheta, _maxTheta;
    bool _isTargetUpdated, _isCameraUpdateRequired;
  };
}

#endif