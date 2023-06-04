class ControllerBase {
    constructor() {
        this._subView = null;
    }

    /**
     * 
     * @param {TSubViewManager} subView 
     */
    onLoad(subView) {
        this._subView = subView;
    }
    onUnload() {
        this._subView = null;
    }
}