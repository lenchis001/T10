#include "Game.h"

#include "boost/bind.hpp"

#include "levels/garage/GarageLevel.h"

namespace T10 {
	Game::~Game()
	{
	}

	void Game::_addLevel(LevelType type, boost::shared_ptr<ILevel> level)
	{
		_levels[type] = level;
	}

	void Game::startGame(boost::shared_ptr<irr::IrrlichtDevice> device)
	{
		device->setEventReceiver(this);
		_sceneManager = device->getSceneManager();
		_guiEnvironment = device->getGUIEnvironment();

		_addLevel(LevelType::MENU, boost::make_shared<GarageLevel>(
			_sceneManager,
			_guiEnvironment,
			boost::bind(&Game::_onSwitchlevelRequested, this, boost::placeholders::_1, boost::placeholders::_2)
			));

		_onSwitchlevelRequested(LevelType::MENU, {});
	}

	void Game::finishGame()
	{
	}

	bool Game::OnEvent(const irr::SEvent& event)
	{
		if (_currentLevel) {
			return _currentLevel->OnEvent(event);
		}

		return false;
	}

	void Game::_onSwitchlevelRequested(LevelType type, map<wstring, wstring> params)
	{
		_guiEnvironment->clear();

		if (_currentLevel) {
			_currentLevel->onUnloadRequested();
		}

		_currentLevel = _levels[type];

		_currentLevel->onLoadRequested();
	}
}