#include "GameInputManager.h"
#include "globals.h"
#include "Game.h"

void GameInputManager::Run() {
    if (SYS_KeyPressed(SYS_KEY_UP) || SYS_KeyPressed(SYS_KEY_W)) {
		game->ProcessInput(Game::Action::MOVE_U);
	}
    if (SYS_KeyPressed(SYS_KEY_DOWN) || SYS_KeyPressed(SYS_KEY_S)) {
		game->ProcessInput(Game::Action::MOVE_D);
	}
    if (SYS_KeyPressed(SYS_KEY_LEFT) || SYS_KeyPressed(SYS_KEY_A)) {
		game->ProcessInput(Game::Action::MOVE_L);
	}
    if (SYS_KeyPressed(SYS_KEY_RIGHT) || SYS_KeyPressed(SYS_KEY_D)) {
		game->ProcessInput(Game::Action::MOVE_R);
	}
	if (SYS_MouseButonPressed(SYS_MB_LEFT) || SYS_KeyPressed(SYS_KEY_SPACE)) {
		game->ProcessInput(Game::Action::SLASH);
	}
}