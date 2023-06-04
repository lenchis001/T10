class Level1Gun {
    constructor(position) {
        this._health = 100;
        this._subScene = null;

        this._buildingProgress = 0;
        this._buildingTime = 5000; // miliseconds

        this._startPosition = position;

        this._constructionCompleteSound = TAMFacade.addSound(Math.random().toString(), "./buildingcomplete.ogg");
    }

    getHelth() {
        return this._health;
    }

    loseHelth(damage) {
        this._health -= damage;
        if (this._health < 0) {
            destruct();
        }
    }

    build() {
        this._subScene = TLMFacade.loadSubScene(Math.random().toString(), "Level1Gun.irr");

        const height = this._getSceneHeight();
        const base = this._subScene.getItem("Base");

        base.setPosition(new TVector3D(this._startPosition.x, this._startPosition.y - height, this._startPosition.z));

        const buildingIteration = this._buildingTime / 100;
        const buildingInterval = setInterval(() => {
            const position = base.getPosition();
            base.setPosition(new TVector3D(position.x, position.y + height / 100, position.z));

            this._buildingProgress++;
            if (this._buildingProgress == 100) {
                clearInterval(buildingInterval);
                this._onBuildingComplete();
            }
        }, buildingIteration);
    }

    destruct() {

    }

    _onBuildingComplete() {
        this._constructionCompleteSound.play(false);
    }

    _getSceneHeight() {
        let result = this._subScene.getItem("Base").getSize().y;

        var gun = this._subScene.getItem("Gun");
        result = Math.max(result, gun.getPosition().y + gun.getSize().y);

        return result;
    }
}