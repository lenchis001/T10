#include "Game.h"

#include "boost/bind.hpp"

#include "levels/garage/GarageLevel.h"
#include "levels/SignIn/SignInLevel.h"

#include "BLL/Services/User/UserService.h"
#include "DAL/ApiServices/User/UserApiService.h"

#include "BLL/Services/Tank/TankService.h"
#include "DAL/ApiServices/Tank/TankApiService.h"

#include "DAL/ApiServices/CommunicationService.h"

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

		boost::shared_ptr<DAL::ApiServices::ICommunicationService> communicationService = boost::make_shared<DAL::ApiServices::CommunicationService>();

		boost::shared_ptr<DAL::ApiServices::User::IUserApiService> userApiService = boost::make_shared<DAL::ApiServices::User::UserApiService>(communicationService);
		boost::shared_ptr<BLL::Services::User::IUserService> userService = boost::make_shared<BLL::Services::User::UserService>(userApiService);

		boost::shared_ptr<DAL::ApiServices::Tanks::ITankApiService> tankApiService = boost::make_shared<DAL::ApiServices::Tanks::TankApiService>(communicationService);
		boost::shared_ptr<BLL::Services::Tanks::ITankService> tankService = boost::make_shared<BLL::Services::Tanks::TankService>(tankApiService);


		_addLevel(LevelType::SIGN_IN, boost::make_shared<Levels::SignInLevel>());

		_addLevel(LevelType::MENU, boost::make_shared<GarageLevel>(
									   _sceneManager,
									   _guiEnvironment,
									   functionsProcessingAware,
									   userService,
									   tankService,
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