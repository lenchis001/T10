interface TVector3D{
    x: Number,
    y: Number,
    z: Number,

    add(otherVector: TVector3D): void;
    sub(otherVector: TVector3D): void;
    mul(otherVector: TVector3D): void;
    div(otherVector: TVector3D): void;
    getCopy(): TVector3D;
    isEqual(otherVector: TVector3D): Boolean;
    rotateXZ(degrees: Number, center: TVector3D): void;
    rotateXY(degrees: Number, center: TVector3D): void;
    rotateYZ(degrees: Number, center: TVector3D): void;
}