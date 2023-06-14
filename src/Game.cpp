#include "Game.h"

#include "boost/bind.hpp"

#include "levels/garage/GarageLevel.h"

#include "bll/services/User/UserService.h"
#include "dal/api_services/User/UserApiService.h"
#include "dal/api_services/CommunicationService.h"

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

		boost::shared_ptr<dal::api_services::ICommunicationService> communicationService = boost::make_shared<dal::api_services::CommunicationService>();
		boost::shared_ptr<dal::api_services::User::IUserApiService> userApiService = boost::make_shared<dal::api_services::User::UserApiService>(communicationService);
		boost::shared_ptr<bll::services::User::IUserService> userService = boost::make_shared<bll::services::User::UserService>(userApiService);

		_addLevel(LevelType::MENU, boost::make_shared<GarageLevel>(
									   _sceneManager,
									   _guiEnvironment,
									   functionsProcessingAware,
									   userService,
									   boost::bind(&Game::_onSwitchlevelRequested, this, boost::placeholders::_1, boost::placeholders::_2)));

		_onSwitchlevelRequested(LevelType::MENU, {});
	}

	void Game::finishGame()
	{
	}

	bool Game::OnEvent(const irr::SEvent &event)
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

		if (_currentLevel)
		{
			_currentLevel->onUnloadRequested();
		}

		_currentLevel = _levels[type];

		_currentLevel->onLoadRequested();
	}
}