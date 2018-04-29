#pragma once

#include "MenuManager.h"
#include "stdafx.h"
#include "swalib/sys.h"
#include "swalib/core.h"

class Button;

class Menu {
public:
    Menu(vec2 _pos, std::string _title);
    virtual ~Menu();
    
    virtual void ProcessInput(
        const MenuManager::Action &action) = 0;
    virtual void Run()    = 0;
    virtual void Render() = 0;

protected:
    std::vector<Button*> buttons;
    Button* activeButton;
    size_t  activeButtonIndex;
    vec2 pos;
    std::string title;
};
