#pragma once

#include "MenuManager.h"
#include "stdafx.h"

class Button;

class Menu {
public:
    Menu() {}
    virtual ~Menu() {}
    
    virtual void ProcessInput(
        const MenuManager::Action &action) = 0;
    virtual void Run()    = 0;
    virtual void Render() = 0;
private:
    std::vector<Button*> buttons;
    Button* activeButton;
};

class DifficultyMenu : public Menu {
public:
    DifficultyMenu()  {}
    ~DifficultyMenu() {}

    void ProcessInput(const MenuManager::Action &action);
    void Run();
    void Render();
};