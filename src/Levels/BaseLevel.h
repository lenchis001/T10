#ifndef BASE_LEVEL
#define BASE_LEVEL

#pragma once

#include "string"
#include "map"

#include "boost/smart_ptr.hpp"
#include "boost/functional.hpp"
#include "boost/filesystem.hpp"

#include "IFunctionsProcessingAware.h"

#include "ILevel.h"
#include "Types.h"

#include "BLL/Services/ResourceLoading/IResourceLoadingService.h"

using namespace std;

namespace T10::Levels
{
#define EXIT_GAME_MESSAGE 10001

	class BaseLevel : public ILevel
	{
	public:
		BaseLevel(
			boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
			boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment,
			boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
			boost::shared_ptr<BLL::Services::ResourceLoading::IResourceLoadingService> resourceLoadingService,
			SwitchLevelCallbackFunction switchLevelCallback);

		virtual void load();

		bool OnEvent(const irr::SEvent& event) override;

	protected:
		virtual void switchToLevel(LevelType type, map<wstring, wstring> params);

		void _exitWithMessage(std::wstring& message);

		boost::shared_ptr<irr::scene::ISceneManager> _sceneManager;
		boost::shared_ptr<irr::gui::IGUIEnvironment> _guiEnvironment;
		boost::shared_ptr<IFunctionsProcessingAware> _functionsProcessingAware;
		boost::shared_ptr<BLL::Services::ResourceLoading::IResourceLoadingService> _resourceLoadingService;
	private:
		SwitchLevelCallbackFunction _switchLevelCallback;
	};
}

#endif // BASE_LEVEL