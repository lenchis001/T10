#ifndef CORRECT_TANK_STATE_MESSAGE_HANDLER_H
#define CORRECT_TANK_STATE_MESSAGE_HANDLER_H

#include "MessageHandlerBase.h"
#include "BLL/Services/BattleState/TankMovingAnimator.h"

#define POSITION_TOLERANCE 3.0F
#define ROTATION_TOLERANCE 3.0F

namespace T10::BLL::Services::BattleState::Tracking::MessageHandling::Handlers {

	class CorrectTankStateMessageHandler : public MessageHandlerBase {
	public:
		CorrectTankStateMessageHandler(boost::shared_ptr<irr::scene::ISceneManager> sceneManager);

		void handle(const boost::json::object& messageBody) override;

	private:
		boost::shared_ptr<irr::scene::ISceneManager> _sceneManager;

		static boost::shared_ptr<irr::scene::ISceneNodeAnimator> _getTankMovingAnimator(boost::shared_ptr<irr::scene::ISceneNode> sceneNode);
		static void _applyPosition(const irr::core::vector3df& value, boost::shared_ptr<irr::scene::ISceneNode> node, bool highPrecision);
		static void _applyRotation(const irr::core::vector3df& value, boost::shared_ptr<irr::scene::ISceneNode> node, bool highPrecision);
	};

}

#endif // CORRECT_TANK_STATE_MESSAGE_HANDLER_H