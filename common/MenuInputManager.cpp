#include "MenuInputManager.h"
#include "globals.h"
#include "MenuManager.h"

#include "stdafx.h"
#include "swalib/sys.h"
#include "swalib/core.h"
#include "swalib/font.h"

void MenuInputManager::Run() {
    if (SYS_KeyPressed(SYS_KEY_UP) || SYS_KeyPressed(SYS_KEY_W)) {
        menuManager->ProcessInput(MenuManager::Action::UP);
	}
    if (SYS_KeyPressed(SYS_KEY_DOWN) || SYS_KeyPressed(SYS_KEY_S)) {
        menuManager->ProcessInput(MenuManager::Action::DOWN);
	}
    if (SYS_KeyPressed(SYS_KEY_LEFT) || SYS_KeyPressed(SYS_KEY_A)) {
        menuManager->ProcessInput(MenuManager::Action::LEFT);
	}
    if (SYS_KeyPressed(SYS_KEY_RIGHT) || SYS_KeyPressed(SYS_KEY_D)) {
        menuManager->ProcessInput(MenuManager::Action::RIGHT);
	}
	if (SYS_MouseButonPressed(SYS_MB_LEFT) || SYS_KeyPressed(SYS_KEY_SPACE)) {
        menuManager->ProcessInput(MenuManager::Action::OK);
	}
    if (SYS_KeyPressed(SYS_KEY_ESC)) {
        menuManager->ProcessInput(MenuManager::Action::BACK);
    }
}