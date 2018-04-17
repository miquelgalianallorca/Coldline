#include "MenuManager.h"
#include "stdafx.h"
#include "Menu.h"

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
        //currentMenu = new MainMenu();
        // HERE!
    }
    else if (ID == MenuID::DIFF) {
        currentMenu = new DifficultyMenu(
            vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 + 50),
            std::string("DIFFICULTY"));
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