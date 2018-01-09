#include "GameStatePlay.h"
#include "globals.h"
#include "Game.h"

GameStatePlay::GameStatePlay() {
    game = new Game();
}

GameStatePlay::~GameStatePlay() {
    delete game;
    game = nullptr;
}

void GameStatePlay::Input() {

}

void GameStatePlay::Run() {
    game->Run();
}

void GameStatePlay::Render() {
    game->Render();
}
