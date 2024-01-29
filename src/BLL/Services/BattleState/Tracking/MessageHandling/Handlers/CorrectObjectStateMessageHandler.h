#ifndef CORRECT_OBJECT_STATE_MESSAGE_HANDLER_H
#define CORRECT_OBJECT_STATE_MESSAGE_HANDLER_H

#include "MessageHandlerBase.h"

namespace T10::BLL::Services::BattleState::Tracking::MessageHandling::Handlers {

	class CorrectObjectStateMessageHandler : public MessageHandlerBase {
	public:
		CorrectObjectStateMessageHandler(boost::shared_ptr<irr::scene::ISceneManager> sceneManager);

		void handle(const boost::json::object& messageBody) override;

	private:
		boost::shared_ptr<irr::scene::ISceneManager> _sceneManager;
	};

}

#endif // CORRECT_OBJECT_STATE_MESSAGE_HANDLER_H