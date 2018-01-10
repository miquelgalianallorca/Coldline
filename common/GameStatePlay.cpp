#include "GameStatePlay.h"
#include "globals.h"
#include "Game.h"

GameStatePlay::GameStatePlay() {
    currentState = StateID::STATE_PLAY;
    changeState  = false;
    game         = new Game();    
}

GameStatePlay::~GameStatePlay() {
    delete game;
    game = nullptr;
}

void GameStatePlay::Input() {

}

void GameStatePlay::Run() {
    game->Run();
    if (game->IsLevelComplete()) {
        nextState   = StateID::STATE_MENU;
        changeState = true;
    }
}

void GameStatePlay::Render() {
    game->Render();
}
