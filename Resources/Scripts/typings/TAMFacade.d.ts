declare var TAMFacade:TAMFacade;

interface TAMFacade{
    addSound(name: String, pathToFile:String): TSoundItem;
    removeSound(name:String): void;
    getItem(name: String): TSoundItem;
}