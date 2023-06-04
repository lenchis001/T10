declare var TUIFacade:TUIFacade;

interface TUIFacade{
    getScreenSize(): TVector2D;
    relativePositionToAbsolute(relativePosition:TVector2D): relativePositionToAbsolute;
    
    loadSubView(viewName: String, fileName: String): TSubViewManager;
    unloadSubView(viewName: String): Boolean;
    isSubViewExist(name: String): Boolean;
    getSubView(name: String): TSubViewManager;

    getCursor(): TCursor;
    setWindowTitle(title: String): void;
}