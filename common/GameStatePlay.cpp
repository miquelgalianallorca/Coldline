#include "GameStatePlay.h"
#include "globals.h"
#include "Game.h"

GameStatePlay::GameStatePlay(Difficulty diff) {
	if (diff == Difficulty::EASY) {
		game = new Game(Game::Difficulty::EASY);
		currentState = StateID::STATE_PLAY_EASY;
		nextState    = StateID::STATE_PLAY_EASY;
	}
	else if (diff == Difficulty::NORMAL) {
		game = new Game(Game::Difficulty::NORMAL);
		currentState = StateID::STATE_PLAY_NORMAL;
		nextState    = StateID::STATE_PLAY_NORMAL;
	}
	else if (diff == Difficulty::HARD) {
		game = new Game(Game::Difficulty::HARD);
		currentState = StateID::STATE_PLAY_NORMAL;
		nextState    = StateID::STATE_PLAY_NORMAL;
	}
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
    if (game->IsLevelComplete() || game->IsPlayerDead()) {
        nextState   = StateID::STATE_MENU;
    }
}

void GameStatePlay::Render() {
    game->Render();
}
