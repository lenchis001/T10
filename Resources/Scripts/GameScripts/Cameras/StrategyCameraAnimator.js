class StrategyCameraAnimator {
    /**
     * 
     * @param {TCameraSubSceneItem} camera 
     */
    constructor(camera) {
        this._camera = camera;

        this._position = new TVector3D(0, 40, 0);

        this._cursor = TUIFacade.getCursor();
        this._oldCursorPosition = new TVector2D(0, 0);

        this._updateCamera();
    }

    onEvent(event) {
        if (event.eventType === TEventTypes.EET_MOUSE_INPUT_EVENT) {
            this._onMouseEvent(event.eventData);
        }
    }

    _onMouseEvent(mouseEventData) {
        if (mouseEventData.Event === TMouseEventTypes.EMIE_LMOUSE_PRESSED_DOWN) {
            this._oldCursorPosition = new TVector2D(mouseEventData.x, mouseEventData.y);

            const result = TLMFacade.getOnNodeCoordinates(this._oldCursorPosition);
        }

        if (mouseEventData.Event === TMouseEventTypes.EMIE_MOUSE_MOVED &&
            mouseEventData.isLeftPressed === "true" /*will be refactored in next releases*/) {
            const mousePosition = new TVector2D(mouseEventData.x, mouseEventData.y);
            const delta = this._oldCursorPosition.sub(mousePosition);
            delta.div(new TVector2D(10, 10));

            this._position.x -= delta.x;
            this._position.z += delta.y;

            this._oldCursorPosition = mousePosition;

            this._updateCamera();
        }
    }

    _updateCamera() {
        this._camera.setPosition(this._position);
        this._camera.setTarget(this._position.getCopy().sub(new TVector3D(0, 1, 1)));
    }
}