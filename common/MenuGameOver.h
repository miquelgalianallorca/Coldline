#pragma once

#include "Menu.h"

class MenuGameOver : public Menu {
public:
    MenuGameOver(vec2 _pos, std::string _title);

    void ProcessInput(const MenuManager::Action &action);
    void Run();
    void Render();

    void NavigateMainMenu();
};