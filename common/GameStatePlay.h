#pragma once

#include "GameState.h"
#include "GameInputManager.h"

class Game;

class GameStatePlay : public GameState {
public:
    GameStatePlay();
    ~GameStatePlay();

    void Input();
    void Run();
    void Render();

private:
    GameInputManager inputManager;
};