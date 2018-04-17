#include "MenuManager.h"
#include "stdafx.h"
#include "MenuDifficulty.h"
#include "MenuLanguage.h"
#include "MenuMain.h"

MenuManager::MenuManager() :
    currentMenu(nullptr),
    changeState(false)
{}

MenuManager::~MenuManager() {
    delete currentMenu;
    currentMenu = nullptr;
}

void MenuManager::SetMenu(MenuID ID) {
    delete currentMenu;
    currentMenu = nullptr;
    // Load new menu
    if (ID == MenuID::MAIN) {
        currentMenu = new MenuMain(
            vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 + 50),
            std::string("COLDLINE"));
    }
    else if (ID == MenuID::DIFF) {
        currentMenu = new MenuDifficulty(
            vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 + 50),
            std::string("DIFFICULTY"));
    }
    else if (ID == MenuID::LANG) {
        currentMenu = new MenuDifficulty(
            vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 + 50),
            std::string("LANGUAGE"));
    }
}

void MenuManager::ProcessInput(Action action) {
    if (currentMenu)
        currentMenu->ProcessInput(action);
}

void MenuManager::Run() {
    if (currentMenu)
        currentMenu->Run();
}

void MenuManager::Render() {
    if (currentMenu)
        currentMenu->Render();
}

void MenuManager::Quit() {

}