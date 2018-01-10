#pragma once

#include "GameState.h"

// Dispatches calls to specific states 
class StateManager {
public:
    StateManager();
    ~StateManager();

    void Input();
    void Run();
    void Render();

private:
    void ChangeState(StateID stateID);

    GameState *state;
};