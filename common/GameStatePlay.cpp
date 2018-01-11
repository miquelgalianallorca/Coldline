#include "GameStatePlay.h"
#include "globals.h"
#include "Game.h"

GameStatePlay::GameStatePlay() {
    currentState = StateID::STATE_PLAY;
    nextState    = StateID::STATE_PLAY;
    game         = new Game();    
}

GameStatePlay::~GameStatePlay() {
    delete game;
    game = nullptr;
}

void GameStatePlay::Input() {
    if (game) inputManager.Run();
}

void GameStatePlay::Run() {
    game->Run();
    if (game->IsLevelComplete()) {
        nextState   = StateID::STATE_MENU;
    }
}

void GameStatePlay::Render() {
    game->Render();
}
