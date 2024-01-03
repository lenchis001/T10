﻿#include "boost/bind.hpp"

#include "Levels/Garage/GarageLevel.hpp"
#include "Levels/SignIn/SignInLevel.hpp"
#include "Levels/Battle/BattleLevel.hpp"

#include "Levels/Garage/BuyTankDialogController.hpp"

#include "Game.h"

#include "BLL/Services/User/UserService.hpp"
#include "DAL/ApiServices/User/UserApiService.hpp"

#include "BLL/Services/Tank/TankService.hpp"
#include "DAL/ApiServices/Tank/TankApiService.hpp"

#include "BLL/Services/TankAssignment/TankAssignmentService.hpp"
#include "DAL/ApiServices/TankAssignment/TankAssignmentApiService.hpp"

#include "DAL/ApiServices/CommunicationService.hpp"
#include "DAL/Services/StorageService.hpp"
#include "DAL/ApiServices/WebSocketApiService.hpp"

#include "BLL/Services/ResourceLoading/ResourceLoadingService.hpp"

#include "BLL/Services/BattleState/BattleStateSynchronizationService.hpp"
#include "BLL/Services/BattleState/Tracking/MessageHandling/MessageHandlerFactory.hpp"
#include "BLL/Services/BattleState/Tracking/MessageHandling/Handlers/CorrectObjectStateMessageHandler.hpp"
#include "BLL/Services/BattleState/Tracking/MessageHandling/Handlers/CorrectTankStateMessageHandler.hpp"
#include "BLL/Services/BattleState/Tracking/MessageHandling/Handlers/SetupSceneMessageHandler.hpp"

boost::shared_ptr<T10::DAL::ApiServices::WebSocketApiService> socketPtr;

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

		auto webSocketApiService = socketPtr = boost::make_shared<DAL::ApiServices::WebSocketApiService>();

		auto messageHandlerFactory = boost::make_shared<BLL::Services::BattleState::Tracking::MessageHandling::MessageHandlerFactory>();
		messageHandlerFactory->addHandler("correctObjectState", boost::make_shared<BLL::Services::BattleState::Tracking::MessageHandling::Handlers::CorrectObjectStateMessageHandler>(_sceneManager));
		messageHandlerFactory->addHandler("correctTankState", boost::make_shared<BLL::Services::BattleState::Tracking::MessageHandling::Handlers::CorrectTankStateMessageHandler>(_sceneManager));
		messageHandlerFactory->addHandler("setupScene", boost::make_shared<BLL::Services::BattleState::Tracking::MessageHandling::Handlers::SetupSceneMessageHandler>(functionsProcessingAware, _sceneManager, resourceLoadingService, userService));

		auto battleStateSynchronizationService = boost::make_shared<BLL::Services::BattleState::BattleStateSynchronizationService>(webSocketApiService, messageHandlerFactory);

		boost::shared_ptr<Levels::Garage::BuyTankDialogController> buyTankDialogController
			= boost::make_shared<Levels::Garage::BuyTankDialogController>(functionsProcessingAware, tankAssignmentService, _guiEnvironment);

		_addLevel(LevelType::SIGN_IN, boost::make_shared<SignIn::SignInLevel>(
			_sceneManager,
			_guiEnvironment,
			functionsProcessingAware,
			resourceLoadingService,
			userService,
			boost::bind(&Game::_onSwitchlevelRequested, this, boost::placeholders::_1, boost::placeholders::_2)));

		_addLevel(LevelType::MENU, boost::make_shared<Garage::GarageLevel>(
			_sceneManager,
			_guiEnvironment,
			functionsProcessingAware,
			resourceLoadingService,
			userService,
			tankService,
			tankAssignmentService,
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