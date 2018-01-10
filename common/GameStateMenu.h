#pragma once

#include "GameState.h"

class GameStateMenu : public GameState {
public:
    GameStateMenu();

    void Input();
    void Run();
    void Render();
};