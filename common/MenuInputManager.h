#pragma once

class MenuInputManager {
public:
    struct KeysDown {
        bool keyUp;
        bool keyDown;
        bool keyLeft;
        bool keyRight;
        bool keyOK;
        bool keyEsc;
    };

    MenuInputManager();

    void Run();
    void ResetKeys();

private:
    KeysDown keysDown;
};