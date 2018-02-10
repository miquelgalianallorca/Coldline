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
	if      (SYS_KeyPressed(SYS_1)) nextState = StateID::STATE_PLAY_EASY;
	else if (SYS_KeyPressed(SYS_2)) nextState = StateID::STATE_PLAY_NORMAL;
	else if (SYS_KeyPressed(SYS_3)) nextState = StateID::STATE_PLAY_HARD;
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