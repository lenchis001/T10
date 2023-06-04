declare var TFileSystem:TFileSystem;

interface TFileSystem{
    readFile(): String;
    writeFile(): void;
    isFileExist(): Boolean;
}