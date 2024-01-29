#ifndef BATTLE_LEVEL_H
#define BATTLE_LEVEL_H

#include "boost/smart_ptr.hpp"
#include "Levels/BaseLevel.h"
#include "Levels/Mixins/LoadingSplashAwareMixin.h"
#include "BLL/Services/User/IUserService.h"
#include "BLL/Services/BattleState/IBattleStateSynchronizationService.h"
#include "Levels/Garage/BuyTankDialogController.h"

namespace T10::Levels::Battle
{
    #define AIM_CONTROL 1

    class BattleLevel : public BaseLevel, public Mixins::LoadingSplashAwareMixin, public boost::enable_shared_from_this<ILevel>
    {
    public:
        BattleLevel(
                boost::shared_ptr<irr::scene::ISceneManager> sceneManager,
                boost::shared_ptr<irr::gui::IGUIEnvironment> guiEnvironment,
                boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware,
                boost::shared_ptr<BLL::Services::ResourceLoading::IResourceLoadingService> resourceLoadingService,
                boost::shared_ptr<irr::gui::ICursorControl> cursorControl,
                boost::shared_ptr<BLL::Services::BattleState::IBattleStateSynchronizationService> battleStateSynchronizationService,
                SwitchLevelCallbackFunction switchLevelCallback);

        void onLoadRequested() override;
        void onUnloadRequested() override;

        bool OnEvent(const irr::SEvent& event) override;

    private:
        boost::shared_ptr<BLL::Services::BattleState::IBattleStateSynchronizationService> _battleStateSynchronizationService;
        boost::shared_ptr<irr::gui::ICursorControl> _cursorControl;

        void _createUi();
        void _createScene();
        void _centerAim();
    };
}

#endif // BATTLE_LEVEL_H