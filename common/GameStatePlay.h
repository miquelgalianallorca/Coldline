#pragma once

#include "GameState.h"

class Game;

class GameStatePlay : public GameState {
public:
    GameStatePlay();
    ~GameStatePlay();

    void Input();
    void Run();
    void Render();
};