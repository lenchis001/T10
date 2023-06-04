dependsOn('GameObjects/Guns/Level1Gun.js');

class CreateGunsEventHandler{
    /**
     * 
     * @param {TSubSceneManager} subScene 
     */
    constructor(subScene){
        this._subScene = subScene;
        this._guns = [];
    }
    
    onEvent(event) {
        if (event.eventType === TEventTypes.EET_MOUSE_INPUT_EVENT) {
            this._onMouseEvent(event.eventData);
        }
    }

    _onMouseEvent(mouseEventData) {
        if (mouseEventData.Event === TMouseEventTypes.EMIE_LMOUSE_PRESSED_DOWN && mouseEventData.Control === "true") {
            const cursorPosition = new TVector2D(mouseEventData.x, mouseEventData.y);
            const result = TLMFacade.getOnNodeCoordinates(cursorPosition);
            if (result) {
                const gun = new Level1Gun(result.position);
                gun.build();
                this._guns.push(gun);
            }
        }
    }
}