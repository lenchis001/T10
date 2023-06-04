declare var TLMFacade:TLMFacade;

type NumberCallback = (n: number) => any;

interface TLMFacade{
    loadSubScene(sceneName: String, levelName:String): TSubSceneManager;
    unloadSubScene(sceneName:String): void;
    isSceneExist(sceneName:String): Boolean;
    getSubScene(sceneName:String): TSubSceneManager;
    getOnNodeCoordinates(cursorPosition: TVector2D): CollisionPointDetectionModel;
}