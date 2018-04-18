#include "MenuDifficulty.h"
#include "Button.h"
#include "globals.h"

MenuDifficulty::MenuDifficulty(vec2 _pos, std::string _title) :
    Menu(_pos, _title)
{
    // Easy
    std::function<void()> executeEasy = std::bind(
        &MenuDifficulty::SetDiffEasy, this);
    Button* easy = new Button(
        vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 50),
        menuManager->strings.easy, executeEasy);
    buttons.push_back(easy);
    // Normal
    std::function<void()> executeNormal = std::bind(
        &MenuDifficulty::SetDiffNormal, this);
    Button* normal = new Button(
        vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 70),
        menuManager->strings.normal, executeNormal);
    buttons.push_back(normal);
    // Hard
    std::function<void()> executeHard = std::bind(
        &MenuDifficulty::SetDiffHard, this);
    Button* hard = new Button(
        vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 90),
        menuManager->strings.hard, executeHard);
    buttons.push_back(hard);

    activeButton = buttons.at(0);
    activeButton->SetActive(true);
}

void MenuDifficulty::ProcessInput(const MenuManager::Action &action) {
    if (action == MenuManager::Action::OK) {
        activeButton->Execute();
    }
    else if (action == MenuManager::Action::DOWN) {
        // Mark next button
        if (activeButtonIndex >= buttons.size() - 1)
            activeButtonIndex = 0;
        else ++activeButtonIndex;

        activeButton->SetActive(false);
        activeButton = buttons.at(activeButtonIndex);
        activeButton->SetActive(true);
    }
    else if (action == MenuManager::Action::UP) {
        // Mark prev button
        if (activeButtonIndex <= 0)
            activeButtonIndex = buttons.size() - 1;
        else --activeButtonIndex;

        activeButton->SetActive(false);
        activeButton = buttons.at(activeButtonIndex);
        activeButton->SetActive(true);
    }
    else if (action == MenuManager::Action::BACK) {
        menuManager->SetMenu(MenuManager::MenuID::MAIN);
    }
}

void MenuDifficulty::Run() {}

void MenuDifficulty::Render() {
    // Render title
    FONT_DrawString(pos, title.data());
    // Render buttons
    for (auto button : buttons) {
        button->Render();
    }
}

void MenuDifficulty::SetDiffEasy() {
    menuManager->SetDifficulty(MenuManager::DiffOpt::EASY);
    menuManager->SetMenu(MenuManager::MenuID::MAIN);
    //menuManager->SetChangeState(true);
}
void MenuDifficulty::SetDiffNormal() {
    menuManager->SetDifficulty(MenuManager::DiffOpt::NORMAL);
    menuManager->SetMenu(MenuManager::MenuID::MAIN);
}
void MenuDifficulty::SetDiffHard() {
    menuManager->SetDifficulty(MenuManager::DiffOpt::HARD);
    menuManager->SetMenu(MenuManager::MenuID::MAIN);
}
