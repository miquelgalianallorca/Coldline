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

    if (!menuManager) {
        menuManager = new MenuManager();
        menuManager->Init();
    }
    else menuManager->SetChangeState(false);
    
    inputManager.ResetKeys();
}

GameStateMenu::~GameStateMenu() {
    delete menuManager;
    menuManager = nullptr;
}

void GameStateMenu::Input() {
    inputManager.Run();
}

void GameStateMenu::Run() {
    if (menuManager) {
        menuManager->Run();
        if (menuManager->GetChangeState()) {
            MenuManager::DiffOpt diff = menuManager->GetDifficulty();
            if (diff == MenuManager::DiffOpt::EASY)
                nextState = StateID::STATE_PLAY_EASY;
            else if (diff == MenuManager::DiffOpt::NORMAL)
                nextState = StateID::STATE_PLAY_NORMAL;
            else if (diff == MenuManager::DiffOpt::HARD)
                nextState = StateID::STATE_PLAY_HARD;
        }
    }
}

void GameStateMenu::Render() {
    if (menuManager)
        menuManager->Render();
}