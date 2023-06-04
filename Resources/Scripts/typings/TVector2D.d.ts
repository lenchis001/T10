interface TVector2D{
    x: Number,
    y: Number,

    add(otherVector: TVector2D): void;
    sub(otherVector: TVector2D): void;
    mul(otherVector: TVector2D): void;
    div(otherVector: TVector2D): void;
    getCopy(): TVector2D;
    isEqual(otherVector: TVector2D): Boolean;
}