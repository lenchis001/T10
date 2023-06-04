interface TSoundItem{
    play(isLoop: Boolean): void;
    pause(): void;
    stop(): void;
    setVolume(value: Number): void;
}