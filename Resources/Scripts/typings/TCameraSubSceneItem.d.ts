interface TCameraSubSceneItem extends TBaseSubSceneItem {
    bindTargetAndRotation(isBind: Boolean): void;
    setTarget(targer: TVector3D): void;
    makeActive(): void;
}