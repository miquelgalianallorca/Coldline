#include "GameInputManager.h"
#include "globals.h"
#include "Game.h"

void GameInputManager::Run() {
    if (SYS_KeyPressed(SYS_KEY_UP))         { game->ProcessInput(Game::Action::MOVE_U); }
    if (SYS_KeyPressed(SYS_KEY_DOWN))       { game->ProcessInput(Game::Action::MOVE_D); }
    if (SYS_KeyPressed(SYS_KEY_LEFT))       { game->ProcessInput(Game::Action::MOVE_L); }
    if (SYS_KeyPressed(SYS_KEY_RIGHT))      { game->ProcessInput(Game::Action::MOVE_R); }
    if (SYS_MouseButonPressed(SYS_MB_LEFT)) { game->ProcessInput(Game::Action::SLASH);  }
}