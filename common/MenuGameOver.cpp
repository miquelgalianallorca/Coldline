#include "MenuGameOver.h"
#include "Button.h"
#include "globals.h"
#include "Game.h"
#include "GraphicsEngine.h"

MenuGameOver::MenuGameOver(vec2 _pos, std::string _title) :
    Menu(_pos, _title)
{
    // Go to Main Menu
    std::function<void()> navDiff = std::bind(
        &MenuGameOver::NavigateMainMenu, this);
    Button* mainmenu = new Button(
        vmake(SCR_WIDTH / 2 - 120, SCR_HEIGHT / 2 - 70),
        menuManager->strings.mainMenu, navDiff);
    buttons.push_back(mainmenu);

    activeButton = buttons.at(0);
    activeButton->SetActive(true);
}

void MenuGameOver::ProcessInput(const MenuManager::Action &action) {
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
        NavigateMainMenu();
    }
}

void MenuGameOver::Run() {}

void MenuGameOver::Render() {
    // Render title
    graphicsEngine->DrawTextLine(pos, title.data());
    // Render buttons
    for (auto button : buttons) {
        button->Render();
    }
}

void MenuGameOver::NavigateMainMenu() {
    menuManager->SetMenu(MenuManager::MenuID::MAIN);
}
