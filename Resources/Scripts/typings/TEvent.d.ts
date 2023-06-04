// {
//     "eventType": "EET_MOUSE_INPUT_EVENT",
//     "eventData": {
//         "Control": "false",
//         "Event": "EMIE_MOUSE_MOVED",
//         "isLeftPressed": "false",
//         "isMiddlePressed": "false",
//         "isRightPressed": "false",
//         "Shift": false,
//         "Wheel": "0.000000",
//         "x": 715,
//         "y": 21
//     }
// }

interface TEventData {
    x: Number,
    y: Number,
    Control: Boolean,
    EventType: String,
    isLeftPressed: Boolean,
    isMiddlePressed: Boolean,
    isRightPressed: Boolean,
    Shift: Boolean,
    Wheel: Number,
    Key: TKeyCode,
    Caller: String
}

interface TEvent {
    eventType: TEventTypes,
    eventData: TEventData
}