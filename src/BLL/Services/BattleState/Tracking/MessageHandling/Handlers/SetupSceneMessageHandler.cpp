#include "SetupSceneMessageHandler.h"

#include "boost/filesystem.hpp"
#include "boost/locale.hpp"

#include "Levels/Cameras/GarageCameraAnimator.h"

using namespace T10::BLL::Services::BattleState::Tracking::MessageHandling::Handlers;

SetupSceneMessageHandler::SetupSceneMessageHandler(
	boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
	boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
	boost::shared_ptr<BLL::Services::ResourceLoading::IResourceLoadingService> resourceLoadingService,
	boost::shared_ptr<BLL::Services::User::IUserService> userService) {
	_functionsProcessingAware = functionsProcessingAware;
	_sceneManager = sceneManager;
	_resourceLoadingService = resourceLoadingService;
	_userService = userService;
}

void SetupSceneMessageHandler::handle(const boost::json::object& messageBody) {
	auto mapName = messageBody.at("map").as_string();
	std::wstring path = boost::filesystem::current_path().append("Resources/Levels").append(mapName).append(std::string(mapName) + ".irr").wstring();
	_functionsProcessingAware->addFuctionToQueue(ThreadTypes::RENDER_THREAD, [&, path]() {
		auto thatPath = path;
		_resourceLoadingService->loadScene(thatPath);
		});

	auto currentUserId = _userService->getCurrentUserId();
	auto players = messageBody.at("players").as_array();

	for (auto& player : players)
	{
		auto& playerObject = player.as_object();

		auto& tankName = player.at("tankName").as_string();
		auto& id = player.at("id").as_int64();
		auto& bodyId = player.at("bodyId").as_int64();

		_functionsProcessingAware->addFuctionToQueue(ThreadTypes::RENDER_THREAD, [=]() {
			_setupTank(currentUserId == id, tankName.data(), bodyId);
			});
	}
}

void SetupSceneMessageHandler::_setupTank(bool isCurrentUser, const std::string& name, int bodyId) {
	auto tankWideName = _toWstring(name);

	auto tank = _resourceLoadingService->loadTank(tankWideName);
	auto body = _sceneManager->getSceneNodeFromName("Body", tank);
	body->setID(bodyId);
	body->addAnimator(boost::make_shared<BLL::Services::BattleState::TankMovingAnimator>(0.01F, 0.04F));

	if (isCurrentUser) {
		auto camera = _sceneManager->addCameraSceneNode();
		camera->addAnimator(
			boost::make_shared<T10::Levels::Cameras::GarageCameraAnimator>(body, 5, 7, 15, 0.2F, irr::core::HALF_PI + 0.2, 300, 0.85F, 1.2F, 3, nullptr));
	}
}

std::wstring SetupSceneMessageHandler::_toWstring(const std::string& value) {
	return boost::locale::conv::utf_to_utf<wchar_t>(value);
}