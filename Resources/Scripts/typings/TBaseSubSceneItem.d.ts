interface TBaseSubSceneItem {
    getSize(): TVector3D;
    getPosition(): TVector3D;
    setPosition(position: TVector3D): void;
    getRotation(): TVector3D;
    setRotation(rotation: TVector3D): void;
    getScale(): TVector3D;
    setScale(scale: TVector3D): void;
    setParent(parent: String): void;
}