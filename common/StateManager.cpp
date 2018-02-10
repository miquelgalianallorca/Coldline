#include "StateManager.h"
#include "GameStateMenu.h"
#include "GameStatePlay.h"

StateManager::StateManager() {
    // Start execution with Menu
    state = new GameStateMenu();
}

StateManager::~StateManager() {
    delete state;
}

void StateManager::Input()  { state->Input();  }
void StateManager::Render() { state->Render(); }

void StateManager::Run() {
    if (state->GetNextState() != state->GetID())
        ChangeState(state->GetNextState());
    state->Run();
}

void StateManager::ChangeState(StateID stateID) {
    GameState *oldState = state;
    GameState *newState;
    switch (stateID) {
        case StateID::STATE_MENU:
			newState = new GameStateMenu();
			break;
		case StateID::STATE_PLAY_EASY:
			newState = new GameStatePlay(GameStatePlay::Difficulty::EASY);
			break;
		case StateID::STATE_PLAY_NORMAL:
			newState = new GameStatePlay(GameStatePlay::Difficulty::NORMAL);
			break;
		case StateID::STATE_PLAY_HARD:
			newState = new GameStatePlay(GameStatePlay::Difficulty::HARD);
			break;
        default:
			newState = new GameStateMenu();
			break;
    }
    state = newState;
    delete oldState;
}