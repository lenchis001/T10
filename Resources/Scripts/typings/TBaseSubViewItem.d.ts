interface TBaseSubViewItem{
    getType(): String;

    isVisible():Boolean;
    setVisible(isVisible:Boolean): void;
    
    isEnabled():Boolean;
    setEnabled(isVisible:Boolean): void;

    remove(): void;

    getPosition(): TVector2D;
    setPosition(position: TVector2D): void;
    getSize(): TVector2D;
    setSize(size: TVector2D): void;

    getText(): String;
    setText(text:String): void;
}