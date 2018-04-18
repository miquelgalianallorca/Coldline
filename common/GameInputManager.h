#pragma once

class GameInputManager {
public:
    struct KeysDown {
        bool keyUp;
        bool keyDown;
        bool keyLeft;
        bool keyRight;
        bool keyOK;
        bool keyEsc;
    };

    GameInputManager();

    void Run();

private:
    KeysDown keysDown;
};