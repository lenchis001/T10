declare var TCursor:TCursor;

interface TCursor{
    setVisible(isVisible:Boolean): void;
    isVisible(): Boolean;
    getPosition(): TVector2D;
    getRelativePosition(): TVector2D;
    setPosition(): void;
    setRelativePosition(): void;
    isEqual(position:TVector2D): Boolean;
}