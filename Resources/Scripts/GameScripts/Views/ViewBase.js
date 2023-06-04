class ViewBase{
    /**
     * 
     * @param {String} path 
     * @param {ControllerBase} controller
     */
    constructor(path, controller){
        this._subView = null;
        this._subViewPath = path;
        this._controller = controller;
    }

    onLoad(){
        this.onUnload();

        this._subView = TUIFacade.loadSubView(Math.random().toString(), this._subViewPath);
        this._controller.onLoad(this._subView);
    }

    onUnload(){
        if(this._subView){
            TUIFacade.unloadSubView(this._subView.getName());
            this._controller.onUnload();
        }
    }

    desctructor(){
        this.onUnload();
    }
}