#pragma once

#include "Menu.h"

class MenuDifficulty : public Menu {
public:
    MenuDifficulty(vec2 _pos, std::string _title);

    void ProcessInput(const MenuManager::Action &action);
    void Run();
    void Render();

    void SetDiffEasy();
    void SetDiffNormal();
    void SetDiffHard();
};