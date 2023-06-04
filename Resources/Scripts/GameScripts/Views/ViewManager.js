dependsOn("GameView.js");
dependsOn("AddBuildingView.js");

const VIEW_NAMES = {
    "GAME_VIEW": "GAME_VIEW",
    "ADD_BUILDING_VIEW": "ADD_BUILDING_VIEW"
};

class ViewManager {
    /**
     * @returns {ViewManager}
     */
    static getInstance() {
        if (!ViewManager._instance) {
            ViewManager._instance = new ViewManager();
        }
        return ViewManager._instance;
    }

    constructor() {
        this._currentView = null;
        
        this._views = {};
        this._loadedView = {};
        this._views[VIEW_NAMES.GAME_VIEW] = new GameView();
        this._views[VIEW_NAMES.ADD_BUILDING_VIEW] = new AddBuildingView();
    }

    /**
     * 
     * @param {String} name 
     * @param {ViewBase} view 
     */
    addView(name, view) {
        this._views[name] = view;
    }

    /**
     * 
     * @param {String} name 
     */
    removeView(name) {
        delete this._views[name];
    }

    /**
     * 
     * @param {String} name 
     */
    changeCurrentView(name) {
        if (this._currentView) {
            this._currentView.onUnload();
        }

        this._currentView = this._views[name];
        this._currentView.onLoad();
    }

    loadView(name){
        this._views[name].onLoad();
    }
    
    unloadView(name){
        this._views[name].onUnload();
    }
}