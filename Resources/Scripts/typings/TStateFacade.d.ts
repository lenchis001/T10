declare var TStateFacade:TStateFacade;

interface TStateFacade{
  getStringProperty(): String;
  setStringProperty(name: String, value: String): void;
  getBoolProperty(): Boolean;
  setBoolProperty(name: String, value: Boolean): void;
  getNumberProperty(): Number;
  setNumberProperty(name: String, value: Number): void;
}