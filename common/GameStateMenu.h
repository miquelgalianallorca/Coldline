#pragma once

#include "GameState.h"
#include "MenuInputManager.h"

class GameStateMenu : public GameState {
public:
    GameStateMenu();
    ~GameStateMenu();

    void Input();
    void Run();
    void Render();

private:
    MenuInputManager inputManager;
};