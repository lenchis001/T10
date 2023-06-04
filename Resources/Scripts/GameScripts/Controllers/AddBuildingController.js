dependsOn('ControllerBase.js');

class AddBuildingController extends ControllerBase {
    constructor() {
        super();

        this._buildings = [
            {
                "text": "Power station",
                "imagePath": "Resources/powerStation1.jpg",
                "description": "A test power station"
            },
            {
                "text": "Dorm",
                "imagePath": "Resources/dorm1.jpg",
                "description": "A test dorm"
            }
        ];
    }

    /**
     * 
     * @param {TSubViewManager} subView 
     */
    onLoad(subView) {
        super.onLoad(subView);

        this._subscriptionName = Math.random().toString();
        TEventsManager.getInstance().subscribe(this._subscriptionName, this);

        this._initializeBuildingsList();
    }

    onUnload() {
        super.onUnload();

        TEventsManager.getInstance().unsubscribe(this._subscriptionName);
    }

    /**
     * 
     * @param {TEvent} event 
     */
    onEvent(event) {
        if (event.eventType === TEventTypes.EET_GUI_EVENT) {
            this._onGuiEvent(event.eventData);
        }
    }

    _onGuiEvent(eventData) {
        switch (eventData.Caller) {
            case "AddBuildingWindow":
                if (eventData.EventType === TGuiEventTypes.EGET_ELEMENT_CLOSED) {
                    ViewManager.getInstance().unloadView(VIEW_NAMES.ADD_BUILDING_VIEW);
                }
                break;
            case "buildingsList":
                if (eventData.EventType === TGuiEventTypes.EGET_LISTBOX_CHANGED) {
                    const selectedOption = this._subView.getItem("buildingsList").getSelectedOption();
                    this._onBuildingListOptionSelected(selectedOption);
                }
                break;
        }
    }

    _onBuildingListOptionSelected(text) {
        const option = this._buildings.find(o => o.text === text);

        if (option) {
            this._subView.getItem("buildingDescription").setText(option.description);
            this._subView.getItem("buildingImage").setPath(option.imagePath);
        }
    }

    _initializeBuildingsList() {
        this._subView.getItem("buildingsList").setOptions(this._buildings.map(b => b.text));
    }
}