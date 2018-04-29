#include "MenuLanguage.h"
#include "Button.h"
#include "globals.h"
#include "GraphicsEngine.h"

MenuLanguage::MenuLanguage(vec2 _pos, std::string _title) :
    Menu(_pos, _title)
{
    // English
    std::function<void()> setEng = std::bind(
        &MenuLanguage::SetLangENG, this);
    Button* eng = new Button(
        vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 50),
        std::string("ENGLISH"), setEng);
    buttons.push_back(eng);
    // Spanish
    std::function<void()> setEsp = std::bind(
        &MenuLanguage::SetLangESP, this);
    Button* esp = new Button(
        vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 70),
        std::string("ESPANOL"), setEsp);
    buttons.push_back(esp);
    // Catalan
    std::function<void()> setCat = std::bind(
        &MenuLanguage::SetLangCAT, this);
    Button* cat = new Button(
        vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 90),
        std::string("CATALA"), setCat);
    buttons.push_back(cat);

    activeButton = buttons.at(0);
    activeButton->SetActive(true);
}

void MenuLanguage::ProcessInput(const MenuManager::Action &action) {
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

void MenuLanguage::Run() {}

void MenuLanguage::Render() {
    // Render title
    graphicsEngine->DrawTextLine(pos, title.data());
    // Render buttons
    for (auto button : buttons) {
        button->Render();
    }
}

void MenuLanguage::SetLangENG() {
    menuManager->SetLanguage(MenuManager::LangOpt::ENG);
    menuManager->SetMenu(MenuManager::MenuID::MAIN);
}
void MenuLanguage::SetLangESP() {
    menuManager->SetLanguage(MenuManager::LangOpt::ESP);
    menuManager->SetMenu(MenuManager::MenuID::MAIN);
}
void MenuLanguage::SetLangCAT() {
    menuManager->SetLanguage(MenuManager::LangOpt::CAT);
    menuManager->SetMenu(MenuManager::MenuID::MAIN);
}
