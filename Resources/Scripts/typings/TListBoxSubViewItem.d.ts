interface TListBoxSubViewItem extends TBaseSubViewItem{
    getOptions():Array<String>;
    setOptions(value: Array<String>): void;
    
    getSelectedOption(): String;
}