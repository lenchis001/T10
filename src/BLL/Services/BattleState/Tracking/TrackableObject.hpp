#ifndef TRACKABLE_OBJECT
#define TRACKABLE_OBJECT

#include "ITrackableObject.h"

namespace T10::BLL::Services::BattleState::Tracking {

	class TrackableObject : ITrackableObject {
	public:
		TrackableObject(boost::shared_ptr<irr::scene::ISceneNode> sceneNode) {
			_sceneNode = sceneNode;
		}

		const irr::core::vector3df& getPosition() const override {
			return _sceneNode->getPosition();
		}

		void setPosition(const irr::core::vector3df& value) override {
			_sceneNode->setPosition(value);
		}

		const irr::core::vector3df& getRotation() const override {
			return _sceneNode->getRotation();
		}

		void setRotation(const irr::core::vector3df& value) override {
			_sceneNode->setRotation(value);
		}

		int getId() const override {
			return _sceneNode->getID();
		}

		bool isDestroyed() const override {
			return false;
		}

	private:
		boost::shared_ptr<irr::scene::ISceneNode> _sceneNode;
	};

}

#endif // TRACKABLE_OBJECT