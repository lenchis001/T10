#ifndef GARAGE_CAMERA_ANIMATOR
#define GARAGE_CAMERA_ANIMATOR

#include "irrlicht.h"
#include "ICameraAnimatorDelegate.h"

namespace T10::Levels::Cameras
{
	const float TWO_PI = irr::core::PI * 2;

	class GarageCameraAnimator : public irr::scene::ISceneNodeAnimator
	{
	public:
		GarageCameraAnimator(
			boost::weak_ptr<irr::scene::ISceneNode> target,
			float minDistance = 4,
			float distance = 5,
			float maxDistance = 6,
			float minTheta = 0.6F,
			float maxTheta = irr::core::HALF_PI - 0.2,
			int sensitivity = 300,
			float phi = 0.85,
			float theta = 1.2,
			float upShift = 0,
			boost::shared_ptr<ICameraAnimatorDelegate> cameraDelegate = nullptr)
		{
			_target = target;
			_minDistance = minDistance;
			_distance = distance;
			_maxDistance = maxDistance;
			_minTheta = minTheta;
			_maxTheta = maxTheta;
			_sensitivity = sensitivity;
			_upShift = upShift;

			assert(_minTheta >= 0);
			assert(maxTheta <= irr::core::PI);
			assert(_sensitivity > 0);

			_phi = phi;
			_theta = theta;
			_recalculatePosition();
			_isCameraUpdateRequired = true;
			_isInitialized = false;

			_cameraDelegate = cameraDelegate;

			// It means that start point is not set yet
			_previousMousePoint.X = -1;

			_recalculatePosition();
		}

		bool OnEvent(const irr::SEvent& event) override
		{
			if (event.EventType == irr::EEVENT_TYPE::EET_MOUSE_INPUT_EVENT)
			{
				_processMouseEvent(event.MouseInput.X, event.MouseInput.Y, event.MouseInput.isLeftPressed(), event.MouseInput.Wheel);

				return true;
			}

			if (_cameraDelegate && _cameraDelegate->OnEvent(event)) {
				return true;
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
			if (_cameraDelegate) {
				_cameraDelegate->animateNode(timeMs);
			}

			auto camera = boost::static_pointer_cast<irr::scene::ICameraSceneNode>(node);
			auto actualTargetPosition = this->_target.lock()->getPosition();

			actualTargetPosition.Y += _upShift;

			if (_lastTrackedPosition != actualTargetPosition || _isCameraUpdateRequired) {
				_lastTrackedPosition = actualTargetPosition;
				_recalculatePosition();
				camera->setPosition(_position);
			}
			else {
				return;
			}

			camera->setTarget(_lastTrackedPosition);

			_isCameraUpdateRequired = false;
			_isInitialized = true;
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

			_position += _lastTrackedPosition;
		}

		void _processMouseEvent(int x, int y, bool isLeftButtonPressed, float wheel)
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

				_previousMousePoint.X = x;
				_previousMousePoint.Y = y;
				_isCameraUpdateRequired = true;
			}
			else
			{
				_previousMousePoint.X = -1;
				_isCameraUpdateRequired = false;
			}


			if (wheel != 0.0F && _distance >= _minDistance && _distance <= _maxDistance) {
				_distance -= wheel / 1.5;

				_distance = min(_distance, _maxDistance);
				_distance = max(_distance, _minDistance);

				_isCameraUpdateRequired = true;
			}

			if (_isCameraUpdateRequired) {
				_recalculatePosition();
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

			_theta = min(_theta, _maxTheta);
			_theta = max(_theta, _minTheta);
		}

		int _sensitivity;
		irr::core::vector2di _previousMousePoint;
		irr::core::vector3df _position, _lastTrackedPosition;
		float _minDistance, _distance, _maxDistance, _phi, _theta, _minTheta, _maxTheta, _upShift;
		bool _isCameraUpdateRequired, _isInitialized;
		boost::weak_ptr<irr::scene::ISceneNode> _target;
		boost::shared_ptr<ICameraAnimatorDelegate> _cameraDelegate;
	};
}

#endif