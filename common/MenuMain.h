#pragma once

#include "Menu.h"

class MenuMain : public Menu {
public:
    MenuMain(vec2 _pos, std::string _title);

    void ProcessInput(const MenuManager::Action &action);
    void Run();
    void Render();

    void NavigatePlay();
    void NavigateDiff();
    void NavigateLang();
    void NavigateQuit();
};