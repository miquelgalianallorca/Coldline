#include "MenuInputManager.h"
#include "globals.h"
#include "MenuManager.h"

#include "stdafx.h"
#include "swalib/sys.h"
#include "swalib/core.h"
#include "swalib/font.h"

MenuInputManager::MenuInputManager() {
    keysDown.keyUp    = false;
    keysDown.keyDown  = false;
    keysDown.keyLeft  = false;
    keysDown.keyRight = false;
    keysDown.keyOK    = false;
    keysDown.keyEsc   = false;
}

void MenuInputManager::Run() {
    if (SYS_KeyPressed(SYS_KEY_UP) || SYS_KeyPressed(SYS_KEY_W)) {
        if (!keysDown.keyUp) {
            menuManager->ProcessInput(MenuManager::Action::UP);
            keysDown.keyUp = true;
        }
	}
    else keysDown.keyUp = false;
    
    if (SYS_KeyPressed(SYS_KEY_DOWN) || SYS_KeyPressed(SYS_KEY_S)) {
        if (!keysDown.keyDown) {
            menuManager->ProcessInput(MenuManager::Action::DOWN);
            keysDown.keyDown = true;
        }
	}
    else keysDown.keyDown = false;

    if (SYS_KeyPressed(SYS_KEY_LEFT) || SYS_KeyPressed(SYS_KEY_A)) {
        if (!keysDown.keyLeft) {
            menuManager->ProcessInput(MenuManager::Action::LEFT);
            keysDown.keyLeft = true;
        }
	}
    else keysDown.keyLeft = false;

    if (SYS_KeyPressed(SYS_KEY_RIGHT) || SYS_KeyPressed(SYS_KEY_D)) {
        if (!keysDown.keyRight) {
            menuManager->ProcessInput(MenuManager::Action::RIGHT);
            keysDown.keyRight = true;
        }
	}
    else keysDown.keyRight = false;

	if (SYS_MouseButonPressed(SYS_MB_LEFT) || SYS_KeyPressed(SYS_KEY_SPACE)) {
        if (!keysDown.keyOK) {
            menuManager->ProcessInput(MenuManager::Action::OK);
            keysDown.keyOK = true;
        }
	}
    else keysDown.keyOK = false;

    if (SYS_KeyPressed(SYS_KEY_ESC)) {
        if (!keysDown.keyEsc) {
            menuManager->ProcessInput(MenuManager::Action::BACK);
            keysDown.keyEsc = true;
        }
    }
    else keysDown.keyEsc = false;
}