#include "string"
#include "map"

#include "boost/smart_ptr.hpp"

#include "IGame.h"

#include "Levels/ILevel.h"
#include "Levels/LevelType.h"

using namespace std;
using namespace T10::Levels;

namespace T10 {
	class Game : public IGame, public irr::IEventReceiver {
	public:
		~Game();

		void startGame(boost::shared_ptr<irr::IrrlichtDevice> device, boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware) override;

		void finishGame() override;

		bool OnEvent(const irr::SEvent& event) override;
	private:
		void _addLevel(LevelType type, boost::shared_ptr<ILevel> level);

		void _onSwitchlevelRequested(LevelType type, map<wstring, wstring> params);

		boost::shared_ptr<ILevel> _currentLevel;
		map<LevelType, boost::shared_ptr<ILevel>> _levels;

		boost::shared_ptr<irr::scene::ISceneManager> _sceneManager;
		boost::shared_ptr<irr::gui::IGUIEnvironment> _guiEnvironment;
	};
}

extern "C" BOOST_SYMBOL_EXPORT T10::Game game;
T10::Game game;