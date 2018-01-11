#include "GameStateMenu.h"

#include "stdafx.h"
#include "swalib\sys.h"
#include "swalib\core.h"
#include "swalib\font.h"

GameStateMenu::GameStateMenu() {
    currentState = StateID::STATE_MENU;
    nextState    = StateID::STATE_MENU;
}

void GameStateMenu::Input() {
    if (SYS_MouseButonPressed(SYS_MB_RIGHT)) {
        nextState   = StateID::STATE_PLAY;
    }
}

void GameStateMenu::Run() {
    //...
}

void GameStateMenu::Render() {
    FONT_DrawString(vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 + 50), "COLDLINE");
    FONT_DrawString(vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 50), "1. EASY");
    FONT_DrawString(vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 70), "2. NORMAL");
    FONT_DrawString(vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 90), "3. HARD");
}