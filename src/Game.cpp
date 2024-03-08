#include "boost/bind.hpp"

#include "Levels/Garage/GarageLevel.h"
#include "Levels/SignIn/SignInLevel.h"
#include "Levels/Battle/BattleLevel.h"

#include "Levels/Garage/BuyTankDialogController.h"

#include "Game.h"

#include "BLL/Services/User/UserService.h"
#include "DAL/ApiServices/User/UserApiService.h"

#include "BLL/Services/Tank/TankService.h"
#include "DAL/ApiServices/Tank/TankApiService.h"

#include "BLL/Services/TankAssignment/TankAssignmentService.h"
#include "DAL/ApiServices/TankAssignment/TankAssignmentApiService.h"

#include "DAL/ApiServices/CommunicationService.h"
#include "DAL/Services/StorageService.h"
#include "DAL/ApiServices/WebSocketApiService.h"
#include "DAL/ApiServices/MatchMaking/MatchMakingApiService.h"

#include "BLL/Services/ResourceLoading/ResourceLoadingService.h"
#include "BLL/Services/MatchMaking/MatchMakingService.h"
#include "BLL/Services/BattleState/BattleStateSynchronizationService.h"
#include "BLL/Services/BattleState/Tracking/MessageHandling/MessageHandlerFactory.h"
#include "BLL/Services/BattleState/Tracking/MessageHandling/Handlers/CorrectObjectStateMessageHandler.h"
#include "BLL/Services/BattleState/Tracking/MessageHandling/Handlers/CorrectTankStateMessageHandler.h"
#include "BLL/Services/BattleState/Tracking/MessageHandling/Handlers/SetupSceneMessageHandler.h"

namespace T10
{
	Game::~Game()
	{
	}

	void Game::_addLevel(LevelType type, boost::shared_ptr<ILevel> level)
	{
		_levels[type] = level;
	}

	void Game::startGame(boost::shared_ptr<irr::IrrlichtDevice> device, boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware)
	{
		device->setEventReceiver(this);
		_sceneManager = device->getSceneManager();
		_guiEnvironment = device->getGUIEnvironment();

		auto communicationService = boost::make_shared<DAL::ApiServices::CommunicationService>();

		auto storageService = boost::make_shared<DAL::Services::StorageService>();

		auto userApiService = boost::make_shared<DAL::ApiServices::User::UserApiService>(communicationService);
		auto userService = boost::make_shared<BLL::Services::User::UserService>(userApiService, communicationService, storageService);

		auto tankApiService = boost::make_shared<DAL::ApiServices::Tanks::TankApiService>(communicationService);
		auto tankService = boost::make_shared<BLL::Services::Tanks::TankService>(tankApiService);

		auto tankAssignmentApiService = boost::make_shared<DAL::ApiServices::TankAssignment::TankAssignmentApiService>(communicationService);
		auto tankAssignmentService = boost::make_shared<BLL::Services::TankAssignment::TankAssignmentService>(tankAssignmentApiService);

		auto resourceLoadingService = boost::make_shared<BLL::Services::ResourceLoading::ResourceLoadingService>(_sceneManager, _guiEnvironment);

		auto matchMakingStateWebSocketApiService = boost::make_shared<DAL::ApiServices::WebSocketApiService>();
		auto matchMakingApiService = boost::make_shared<DAL::ApiServices::MatchMaking::MatchMakingApiService>(storageService, matchMakingStateWebSocketApiService);
		auto matchMakingService = boost::make_shared<BLL::Services::MatchMaking::MatchMakingService>(matchMakingApiService, storageService);

		auto battleStateWebSocketApiService = boost::make_shared<DAL::ApiServices::WebSocketApiService>();

		auto messageHandlerFactory = boost::make_shared<BLL::Services::BattleState::Tracking::MessageHandling::MessageHandlerFactory>();
		messageHandlerFactory->addHandler("correctObjectState", boost::make_shared<BLL::Services::BattleState::Tracking::MessageHandling::Handlers::CorrectObjectStateMessageHandler>(_sceneManager));
		messageHandlerFactory->addHandler("correctTankState", boost::make_shared<BLL::Services::BattleState::Tracking::MessageHandling::Handlers::CorrectTankStateMessageHandler>(_sceneManager));
		messageHandlerFactory->addHandler("setupScene", boost::make_shared<BLL::Services::BattleState::Tracking::MessageHandling::Handlers::SetupSceneMessageHandler>(functionsProcessingAware, _sceneManager, resourceLoadingService, userService));

		auto battleStateSynchronizationService = boost::make_shared<BLL::Services::BattleState::BattleStateSynchronizationService>(battleStateWebSocketApiService, messageHandlerFactory);

		boost::shared_ptr<Levels::Garage::StartBattleDialogController> startBattleDialogController
			= boost::make_shared<Levels::Garage::StartBattleDialogController>(functionsProcessingAware, matchMakingService, _guiEnvironment);
		boost::shared_ptr<Levels::Garage::BuyTankDialogController> buyTankDialogController
			= boost::make_shared<Levels::Garage::BuyTankDialogController>(functionsProcessingAware, tankAssignmentService, _guiEnvironment);

		_addLevel(LevelType::SIGN_IN, boost::make_shared<SignIn::SignInLevel>(
			_sceneManager,
			_guiEnvironment,
			functionsProcessingAware,
			resourceLoadingService,
			userService,
			boost::bind(&Game::_onSwitchlevelRequested, this, boost::placeholders::_1, boost::placeholders::_2)));

		matchMakingService->setBattleStartedHandler([=]() {
			_onSwitchlevelRequested(LevelType::GAME, {});
			});
		_addLevel(LevelType::GARAGE, boost::make_shared<Garage::GarageLevel>(
			_sceneManager,
			_guiEnvironment,
			functionsProcessingAware,
			resourceLoadingService,
			userService,
			tankService,
			tankAssignmentService,
			startBattleDialogController,
			buyTankDialogController,
			boost::bind(&Game::_onSwitchlevelRequested, this, boost::placeholders::_1, boost::placeholders::_2)));

		auto cursorControl = device->getCursorControl();
		_addLevel(LevelType::GAME, boost::make_shared<Battle::BattleLevel>(
			_sceneManager,
			_guiEnvironment,
			functionsProcessingAware,
			resourceLoadingService,
			cursorControl,
			battleStateSynchronizationService,
			boost::bind(&Game::_onSwitchlevelRequested, this, boost::placeholders::_1, boost::placeholders::_2)));

		_onSwitchlevelRequested(LevelType::SIGN_IN, {});
	}

	void Game::finishGame()
	{
	}

	bool Game::OnEvent(const irr::SEvent& event)
	{
		if (_currentLevel)
		{
			return _currentLevel->OnEvent(event);
		}

		return false;
	}

	void Game::_onSwitchlevelRequested(LevelType type, map<wstring, wstring> params)
	{
		_guiEnvironment->clear();
		_sceneManager->clear();

		if (_currentLevel)
		{
			_currentLevel->onUnloadRequested();
		}

		_currentLevel = _levels[type];

		_currentLevel->onLoadRequested();
	}
}