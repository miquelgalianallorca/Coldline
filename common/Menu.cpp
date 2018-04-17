#include "Menu.h"
#include "Button.h"
#include "globals.h"

Menu::Menu(vec2 _pos, std::string _title) :
    pos(_pos),
    title(_title),
    activeButtonIndex(0)
{}

Menu::~Menu() {
    for (auto button : buttons)
        delete button;
    buttons.clear();
}

// DIFFICULTY ======================================================
DifficultyMenu::DifficultyMenu(vec2 _pos, std::string _title) :
    Menu(_pos, _title)
{
    // Easy
    std::function<void()> executeEasy = std::bind(
        &DifficultyMenu::SetDiffEasy, this);
    Button* easy = new Button(
        vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 50),
        std::string("EASY"), executeEasy);
    buttons.push_back(easy);
    // Normal
    std::function<void()> executeNormal = std::bind(
        &DifficultyMenu::SetDiffNormal, this);
    Button* normal = new Button(
        vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 70),
        std::string("NORMAL"), executeNormal);
    buttons.push_back(normal);
    // Hard
    std::function<void()> executeHard = std::bind(
        &DifficultyMenu::SetDiffHard, this);
    Button* hard = new Button(
        vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 90),
        std::string("HARD"), executeHard);
    buttons.push_back(hard);

    activeButton = buttons.at(0);
    activeButton->SetActive(true);
}

void DifficultyMenu::ProcessInput(const MenuManager::Action &action) {
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

void DifficultyMenu::Run() {}

void DifficultyMenu::Render() {
    // Render title
    FONT_DrawString(pos, title.data());
    // Render buttons
    for (auto button : buttons) {
        button->Render();
    }
}

void DifficultyMenu::SetDiffEasy() {
    menuManager->SetDifficulty(MenuManager::DiffOpt::EASY);
    menuManager->SetMenu(MenuManager::MenuID::MAIN);
    //menuManager->SetChangeState(true);
}
void DifficultyMenu::SetDiffNormal() {
    menuManager->SetDifficulty(MenuManager::DiffOpt::NORMAL);
    menuManager->SetMenu(MenuManager::MenuID::MAIN);
}
void DifficultyMenu::SetDiffHard() {
    menuManager->SetDifficulty(MenuManager::DiffOpt::HARD);
    menuManager->SetMenu(MenuManager::MenuID::MAIN);
}

// =================================================================

