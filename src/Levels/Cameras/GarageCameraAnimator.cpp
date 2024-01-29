#include "GarageCameraAnimator.h"

#include "algorithm"

using namespace T10::Levels::Cameras;

GarageCameraAnimator::GarageCameraAnimator(
	boost::weak_ptr<irr::scene::ISceneNode> target,
	float minDistance,
	float distance,
	float maxDistance,
	float minTheta,
	float maxTheta,
	int sensitivity,
	float phi,
	float theta,
	float upShift,
	boost::shared_ptr<ICameraAnimatorDelegate> cameraDelegate)
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

	_cameraDelegate = cameraDelegate;

	// It means that start point is not set yet
	_previousMousePoint.X = -1;

	_recalculatePosition();
}

bool GarageCameraAnimator::OnEvent(const irr::SEvent& event)
{
	if (_cameraDelegate && _cameraDelegate->OnEvent(event)) {
		return true;
	}

	if (event.EventType == irr::EEVENT_TYPE::EET_MOUSE_INPUT_EVENT)
	{
		_processMouseEvent(event.MouseInput.X, event.MouseInput.Y, event.MouseInput.isLeftPressed(), event.MouseInput.Wheel);

		return true;
	}

	return ISceneNodeAnimator::OnEvent(event);
}

boost::shared_ptr<irr::scene::ISceneNodeAnimator> GarageCameraAnimator::createClone(boost::shared_ptr<irr::scene::ISceneNode> node,
	boost::shared_ptr<irr::scene::ISceneManager> newManager)
{
	return boost::make_shared<GarageCameraAnimator>(_target, _distance);
}

void GarageCameraAnimator::animateNode(boost::shared_ptr<irr::scene::ISceneNode> node, irr::u32 timeMs)
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
}

bool GarageCameraAnimator::isEventReceiverEnabled() const
{
	return true;
}

void GarageCameraAnimator::_recalculatePosition()
{
	_position.X = _distance * sin(_theta) * cos(_phi);
	_position.Y = _distance * cos(_theta);
	_position.Z = _distance * sin(_theta) * sin(_phi);

	_position += _lastTrackedPosition;
}

void GarageCameraAnimator::_processMouseEvent(int x, int y, bool isLeftButtonPressed, float wheel)
{
	if (isLeftButtonPressed)
	{
		if (_previousMousePoint.X < 0)
		{
			_previousMousePoint.X = x;
			_previousMousePoint.Y = y;

			// it's the first event for this manipulation
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

		_distance = std::min(_distance, _maxDistance);
		_distance = std::max(_distance, _minDistance);

		_isCameraUpdateRequired = true;
	}

	if (_isCameraUpdateRequired) {
		_recalculatePosition();
	}
}

void GarageCameraAnimator::_calculateInclination(float xDelta, float yDelta)
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

	_theta = std::min(_theta, _maxTheta);
	_theta = std::max(_theta, _minTheta);
}