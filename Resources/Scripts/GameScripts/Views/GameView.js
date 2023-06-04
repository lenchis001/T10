dependsOn("ViewBase.js");

dependsOn("../Controllers/GameController.js")

class GameView extends ViewBase {
    constructor(){
        super("HUD.xml", new GameController());
    }
}