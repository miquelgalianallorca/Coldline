#include "StateManager.h"
#include "GameStateMenu.h"
#include "GameStatePlay.h"

StateManager::StateManager() {
    //state = new GameStatePlay();
    state = new GameStateMenu();
}

StateManager::~StateManager() {
    delete state;
}

void StateManager::Input()  { state->Input();  }
void StateManager::Render() { state->Render(); }

void StateManager::Run() {
    if (state->GetChangeState())
        ChangeState(state->GetNextState());
    state->Run();
}


void StateManager::ChangeState(StateID stateID) {
    GameState *oldState = state;
    GameState *newState;
    switch (stateID) {
        case StateID::STATE_MENU: newState = new GameStateMenu(); break;
        case StateID::STATE_PLAY: newState = new GameStatePlay(); break;
        default:                  newState = new GameStatePlay(); break;
    }
    state = newState;
    delete oldState;
}