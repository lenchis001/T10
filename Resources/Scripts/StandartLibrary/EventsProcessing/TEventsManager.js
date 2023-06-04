// Scheme of event handlers
// eventHandlers -> eventType -> eventValue
// For example
// eventHandlers -> KEYBOARD_EVENT -> KEY_B
class TEventsManager {
  /**
   * @return {TEventsManager}
   */
  static getInstance() {
    if (!TEventsManager._instance) {
      TEventsManager._instance = new TEventsManager();
    }
    return TEventsManager._instance;
  }

  constructor() {
    this.eventHandlers = {};
  }

  /**
   *
   * @param {Object} event
   * // For example: KEYBOARD_EVENT
   * @param {Object} event.eventType
   * // For example: KEY_B
   * @param {Object} event.eventData
   */
  _onEvent(event) {
    const correctedEventData = this._correctEventData(event.eventData);

    event.eventData = correctedEventData;

    for (const handlerName in this.eventHandlers) {
      this.eventHandlers[handlerName].onEvent(event);
    }
  }
  /**
   *
   * @param {string} handlerName
   * @param {object} handler
   */
  subscribe(handlerName, handler) {
    this.eventHandlers[handlerName] = handler;
  }
  /**
   *
   * @param {string} handlerName
   */
  unsubscribe(handlerName) {

    if (this.eventHandlers[handlerName] && this.eventHandlers[handlerName].destructor)
      this.eventHandlers[handlerName].destructor();

    delete this.eventHandlers[handlerName];
  }

  _correctEventData(data) {
    const result = Object.assign({}, data);

    result.Shift = result.Shift === 'true';
    result.x = parseInt(data.x);
    result.y = parseInt(data.y);

    return result;
  }
}

function __onEvent(event) {
  TEventsManager.getInstance()._onEvent(JSON.parse(event));
}
