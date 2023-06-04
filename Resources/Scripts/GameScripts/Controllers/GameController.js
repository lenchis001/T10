dependsOn('../Cameras/StrategyCameraAnimator.js');
dependsOn('../CreateGunsEventHandler.js')

dependsOn('ControllerBase.js');

var ACTIVE_SUBSCENE_NAME = "active sub scene";

class GameController extends ControllerBase {
    onLoad(subView) {
        super.onLoad();

        this._environmentSoundName = Math.random().toString();
        TAMFacade
            .addSound(this._environmentSoundName, "environment1.ogg")
            .play(true);
        TAMFacade.getItem(this._environmentSoundName).setVolume(0.3);

        let subScene = TLMFacade.loadSubScene(ACTIVE_SUBSCENE_NAME, "FlatLevel.irr", true);
        let camera = subScene.addCamera(true);

        TEventsManager.getInstance().subscribe("Create gun handler", new CreateGunsEventHandler(subScene));
        TEventsManager.getInstance().subscribe("Camera handler", new StrategyCameraAnimator(camera));

        this._eventsSubscriptionName = Math.random().toString();
        TEventsManager.getInstance().subscribe(this._eventsSubscriptionName, this);
    }

    onUnload() {
        TEventsManager.getInstance().unsubscribe(this._eventsSubscriptionName);
        TAMFacade.removeSound(this._environmentSoundName);
    }

    /**
     * 
     * @param {TEvent} event 
     */
    onEvent(event) {
        if (event.eventType === TEventTypes.EET_GUI_EVENT) {
            switch (event.eventData.Caller) {
                case "addBuilding":
                    switch (event.eventData.EventType) {
                        case TGuiEventTypes.EGET_BUTTON_CLICKED:
                            this._onAddBuildingClicked();
                            break;
                    }
                    break;
            }
        }
    }

    _onAddBuildingClicked() {
        ViewManager.getInstance().loadView(VIEW_NAMES.ADD_BUILDING_VIEW);
    }
}
