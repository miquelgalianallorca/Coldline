#include "MenuInGame.h"
#include "Button.h"
#include "globals.h"
#include "Game.h"

MenuInGame::MenuInGame(vec2 _pos, std::string _title) :
    Menu(_pos, _title)
{
    // Close InGame Menu
    std::function<void()> navPlay = std::bind(
        &MenuInGame::CloseInGameMenu, this);
    Button* close = new Button(
        vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 50),
        std::string("CLOSE"), navPlay);
    buttons.push_back(close);
    // Go to Main Menu
    std::function<void()> navDiff = std::bind(
        &MenuInGame::NavigateMainMenu, this);
    Button* mainmenu = new Button(
        vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 70),
        std::string("MAIN MENU"), navDiff);
    buttons.push_back(mainmenu);

    activeButton = buttons.at(0);
    activeButton->SetActive(true);
}

void MenuInGame::ProcessInput(const MenuManager::Action &action) {
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
    /*else if (action == MenuManager::Action::BACK) {
        menuManager->Quit();
    }*/
}

void MenuInGame::Run() {}

void MenuInGame::Render() {
    // Render title
    FONT_DrawString(pos, title.data());
    // Render buttons
    for (auto button : buttons) {
        button->Render();
    }
}

void MenuInGame::CloseInGameMenu() {
    //menuManager->SetChangeState(true);
    game->ToggleInGameMenu();
}

void MenuInGame::NavigateMainMenu() {
    //menuManager->SetMenu(MenuManager::MenuID::DIFF);
    game->KillPlayer();
}
