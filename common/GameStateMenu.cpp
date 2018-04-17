#include "GameStateMenu.h"

#include "globals.h"
#include "MenuManager.h"
#include "Menu.h"

#include "stdafx.h"
#include "swalib/sys.h"
#include "swalib/core.h"
#include "swalib/font.h"

GameStateMenu::GameStateMenu() {
    currentState = StateID::STATE_MENU;
    nextState    = StateID::STATE_MENU;

    menuManager  = new MenuManager();
    menuManager->SetMenu(MenuManager::MenuID::DIFF);
}

GameStateMenu::~GameStateMenu() {
    delete menuManager;
    menuManager = nullptr;
}

void GameStateMenu::Input() {
    inputManager.Run();

	/*if      (SYS_KeyPressed(SYS_1)) nextState = StateID::STATE_PLAY_EASY;
	else if (SYS_KeyPressed(SYS_2)) nextState = StateID::STATE_PLAY_NORMAL;
	else if (SYS_KeyPressed(SYS_3)) nextState = StateID::STATE_PLAY_HARD;*/
}

void GameStateMenu::Run() {
    if (menuManager) {
        menuManager->Run();
        if (menuManager->GetChangeState())
            nextState = StateID::STATE_PLAY_NORMAL;
        // TO DO...
    }
}

void GameStateMenu::Render() {
    if (menuManager)
        menuManager->Render();    
    /*FONT_DrawString(vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 + 50), "COLDLINE");
    FONT_DrawString(vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 50), "1. EASY");
    FONT_DrawString(vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 70), "2. NORMAL");
    FONT_DrawString(vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 90), "3. HARD");*/
}