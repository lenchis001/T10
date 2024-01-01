#ifndef CORRECT_OBJECT_STATE_MESSAGE_HANDLER
#define CORRECT_OBJECT_STATE_MESSAGE_HANDLER

#include "MessageHandlerBase.hpp"

namespace T10::BLL::Services::BattleState::Tracking::MessageHandling::Handlers {
	
	class CorrectObjectStateMessageHandler : public MessageHandlerBase {
	public:
		CorrectObjectStateMessageHandler(boost::shared_ptr<irr::scene::ISceneManager> sceneManager) {
			_sceneManager = sceneManager;
		}

		void handle(const boost::json::object& messageBody) override {
			auto id = messageBody.at("id").as_int64();
			auto position = _parseVector(messageBody.at("position").as_object());
			auto rotation = _parseVector(messageBody.at("rotation").as_object());

			auto targetObject = _sceneManager->getSceneNodeFromId(id);

			if (targetObject) {
				targetObject->setPosition(position);
				targetObject->setRotation(rotation);
			}
			else {
				// todo: add logs
			}
		}
	private:
		boost::shared_ptr<irr::scene::ISceneManager> _sceneManager;
	};

}

#endif // CORRECT_OBJECT_STATE_MESSAGE_HANDLER