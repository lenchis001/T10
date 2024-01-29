#ifndef GARAGE_CAMERA_ANIMATOR_H
#define GARAGE_CAMERA_ANIMATOR_H

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
			boost::shared_ptr<ICameraAnimatorDelegate> cameraDelegate = nullptr);

		bool OnEvent(const irr::SEvent& event) override;
		boost::shared_ptr<irr::scene::ISceneNodeAnimator> createClone(boost::shared_ptr<irr::scene::ISceneNode> node,
			boost::shared_ptr<irr::scene::ISceneManager> newManager = 0) override;
		void animateNode(boost::shared_ptr<irr::scene::ISceneNode> node, irr::u32 timeMs) override;
		bool isEventReceiverEnabled() const override;

	private:
		void _recalculatePosition();
		void _processMouseEvent(int x, int y, bool isLeftButtonPressed, float wheel);
		void _calculateInclination(float xDelta, float yDelta);

		int _sensitivity;
		irr::core::vector2di _previousMousePoint;
		irr::core::vector3df _position, _lastTrackedPosition;
		float _minDistance, _distance, _maxDistance, _phi, _theta, _minTheta, _maxTheta, _upShift;
		bool _isCameraUpdateRequired;
		boost::weak_ptr<irr::scene::ISceneNode> _target;
		boost::shared_ptr<ICameraAnimatorDelegate> _cameraDelegate;
	};
}

#endif // GARAGE_CAMERA_ANIMATOR_H