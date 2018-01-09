#pragma once

#include "GameState.h"

class GameStateMenu : public GameState {
public:
    void Input();
    void Run();
    void Render();
    StateID GetID() { return StateID::STATE_MENU; }
};