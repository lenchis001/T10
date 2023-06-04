dependsOn("ViewBase.js");

dependsOn("../Controllers/AddBuildingController.js")

class AddBuildingView extends ViewBase {
    constructor() {
        super("AddBuilding.xml", new AddBuildingController());
    }
}