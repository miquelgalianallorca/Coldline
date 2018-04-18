#pragma once

#include "Menu.h"

class MenuInGame : public Menu {
public:
    MenuInGame(vec2 _pos, std::string _title);

    void ProcessInput(const MenuManager::Action &action);
    void Run();
    void Render();

    void CloseInGameMenu();
    void NavigateMainMenu();
};