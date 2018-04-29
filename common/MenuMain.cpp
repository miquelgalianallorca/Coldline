#include "MenuMain.h"
#include "Button.h"
#include "globals.h"
#include "GraphicsEngine.h"

MenuMain::MenuMain(vec2 _pos, std::string _title) :
    Menu(_pos, _title)
{
    // Play
    std::function<void()> navPlay = std::bind(
        &MenuMain::NavigatePlay, this);
    Button* play = new Button(
        vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 50),
        menuManager->strings.play, navPlay);
    buttons.push_back(play);
    // Difficulty
    std::function<void()> navDiff = std::bind(
        &MenuMain::NavigateDiff, this);
    Button* diff = new Button(
        vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 70),
        menuManager->strings.difficulty, navDiff);
    buttons.push_back(diff);
    // Language
    std::function<void()> navLang = std::bind(
        &MenuMain::NavigateLang, this);
    Button* lang = new Button(
        vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 90),
        menuManager->strings.language, navLang);
    buttons.push_back(lang);
    // Language
    std::function<void()> navQuit = std::bind(
        &MenuMain::NavigateQuit, this);
    Button* quit = new Button(
        vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 110),
        menuManager->strings.quit, navQuit);
    buttons.push_back(quit);

    activeButton = buttons.at(0);
    activeButton->SetActive(true);
}

void MenuMain::ProcessInput(const MenuManager::Action &action) {
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
        menuManager->Quit();
    }
}

void MenuMain::Run() {}

void MenuMain::Render() {
    // Render title
    graphicsEngine->DrawTextLine(pos, title.data());
    // Render buttons
    for (auto button : buttons) {
        button->Render();
    }
}

void MenuMain::NavigatePlay() {
    menuManager->SetChangeState(true);
}

void MenuMain::NavigateDiff() {
    menuManager->SetMenu(MenuManager::MenuID::DIFF);
}

void MenuMain::NavigateLang() {
    menuManager->SetMenu(MenuManager::MenuID::LANG);
}

void MenuMain::NavigateQuit() {
    menuManager->Quit();
}
