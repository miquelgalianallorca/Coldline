#pragma once

#include "Menu.h"

class MenuLanguage : public Menu {
public:
    MenuLanguage(vec2 _pos, std::string _title);

    void ProcessInput(const MenuManager::Action &action);
    void Run();
    void Render();

    void SetLangENG();
    void SetLangESP();
    void SetLangCAT();
};