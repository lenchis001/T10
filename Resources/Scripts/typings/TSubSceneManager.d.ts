interface TSubSceneManager{
    getName(): String;
    removeItem(name: String): Boolean;
    isItemExist(name: String): Boolean;
    getItem(name: String): TBaseSubSceneItem;
    addMesh(path: String): TBaseSubSceneItem;
    addOstreeMesh(path: String): TBaseSubSceneItem;
    addWaterSurface(path: String): TBaseSubSceneItem;
    addTerrainFromHeightmap(path: String): TBaseSubSceneItem;
    addSkySphere(path: String): TBaseSubSceneItem;
    addSkyCube(): TBaseSubSceneItem;
    addLightSource(): TBaseSubSceneItem;
    addCamera(path: String): TCameraSubSceneItem;
}