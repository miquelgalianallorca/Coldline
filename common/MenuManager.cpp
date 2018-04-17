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
    if (ID == MenuID::DIFF) {
        currentMenu = new DifficultyMenu();
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