#ifndef TANK_MOVING_ANIMATOR
#define TANK_MOVING_ANIMATOR

#include "irrlicht.h"

namespace T10::Levels::Battle::Tank {
	class TankMovingAnimator : public irr::scene::ISceneNodeAnimator {
	public:
		//! Animates a scene node.
		/** \param node Node to animate.
		\param timeMs Current time in milli seconds. */
		virtual void animateNode(boost::shared_ptr<irr::scene::ISceneNode> node, irr::u32 timeMs) {
			auto position = node->getPosition();
			position.X += timeMs;

			node->setPosition(position/500);
		}

		//! Creates a clone of this animator.
		/** Please note that you will have to drop
		(IReferenceCounted::drop()) the returned pointer after calling this. */
		virtual boost::shared_ptr<ISceneNodeAnimator> createClone(boost::shared_ptr<irr::scene::ISceneNode> node,
			boost::shared_ptr<irr::scene::ISceneManager> newManager = 0) {
			return nullptr;
		}

		//! Returns true if this animator receives events.
		/** When attached to an active camera, this animator will be
		able to respond to events such as mouse and keyboard events. */
		virtual bool isEventReceiverEnabled() const
		{
			return false;
		}

		//! Event receiver, override this function for camera controlling animators
		virtual bool OnEvent(const irr::SEvent& event)
		{
			return false;
		}

		//! Returns type of the scene node animator
		virtual irr::scene::ESCENE_NODE_ANIMATOR_TYPE getType() const
		{
			return irr::scene::ESCENE_NODE_ANIMATOR_TYPE::ESNAT_UNKNOWN;
		}

		//! Returns if the animator has finished.
		/** This is only valid for non-looping animators with a discrete end state.
		\return true if the animator has finished, false if it is still running. */
		virtual bool hasFinished(void) const
		{
			return false;
		}
	};
} // T10::Levels::Battle::Tank

#endif // TANK_MOVING_ANIMATOR