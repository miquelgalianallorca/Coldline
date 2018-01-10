#include "GameStateMenu.h"

#include "stdafx.h"
#include "swalib\sys.h"
#include "swalib\core.h"
#include "swalib\font.h"

GameStateMenu::GameStateMenu() {
    currentState = StateID::STATE_MENU;
    changeState  = false;
}

void GameStateMenu::Input() {
    if (SYS_MouseButonPressed(SYS_MB_RIGHT)) {
        changeState = true;
        nextState   = StateID::STATE_PLAY;
    }
}

void GameStateMenu::Run() {
    //...
}

void GameStateMenu::Render() {
    FONT_DrawString(vmake(SCR_WIDTH/2 - 80, SCR_HEIGHT/2), "COLDLINE");
}