#include "GameInputManager.h"
#include "globals.h"
#include "Game.h"
#include "MenuManager.h"

GameInputManager::GameInputManager() {
    keysDown.keyUp    = false;
    keysDown.keyDown  = false;
    keysDown.keyLeft  = false;
    keysDown.keyRight = false;
    keysDown.keyOK    = false;
    keysDown.keyEsc   = false;
}

void GameInputManager::Run() {
    if (SYS_KeyPressed(SYS_KEY_UP) || SYS_KeyPressed(SYS_KEY_W)) {
        if (!game->GetIsInGameMenuOpen()) {
            game->ProcessInput(Game::Action::MOVE_U);
        }
        if (!keysDown.keyUp) {
            if (game->GetIsInGameMenuOpen()) {
                if (menuManager)
                    menuManager->ProcessInput(MenuManager::Action::UP);
            }
            keysDown.keyUp = true;
        }
    }
    else keysDown.keyUp = false;

    if (SYS_KeyPressed(SYS_KEY_DOWN) || SYS_KeyPressed(SYS_KEY_S)) {
        if (!game->GetIsInGameMenuOpen()) {
            game->ProcessInput(Game::Action::MOVE_D);
        }
        if (!keysDown.keyDown) {
            if (game->GetIsInGameMenuOpen()) {
                if (menuManager)
                    menuManager->ProcessInput(MenuManager::Action::DOWN);
            }
            keysDown.keyDown = true;
        }
	}
    else keysDown.keyDown = false;

    if (SYS_KeyPressed(SYS_KEY_LEFT) || SYS_KeyPressed(SYS_KEY_A)) {
		game->ProcessInput(Game::Action::MOVE_L);
        if (!keysDown.keyLeft) {
            keysDown.keyLeft = true;
        }
	}
    else keysDown.keyLeft = false;

    if (SYS_KeyPressed(SYS_KEY_RIGHT) || SYS_KeyPressed(SYS_KEY_D)) {
		game->ProcessInput(Game::Action::MOVE_R);
        if (!keysDown.keyRight) {
            keysDown.keyRight = true;
        }
	}
    else keysDown.keyRight = false;
	
    if (SYS_MouseButonPressed(SYS_MB_LEFT) || SYS_KeyPressed(SYS_KEY_SPACE)) {
        if (!game->GetIsInGameMenuOpen()) {
            game->ProcessInput(Game::Action::SLASH);
        }
        else {
            if (menuManager)
                menuManager->ProcessInput(MenuManager::Action::OK);
        }
        keysDown.keyOK = true;
	}
    else keysDown.keyOK = false;

    if (SYS_KeyPressed(SYS_KEY_ESC)) {
        if (!keysDown.keyEsc) {
            game->ToggleInGameMenu();
            keysDown.keyEsc = true;
        }
    }
    else keysDown.keyEsc = false;
}