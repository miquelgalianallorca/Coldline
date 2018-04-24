#include "MenuManager.h"
#include "stdafx.h"
#include "MenuDifficulty.h"
#include "MenuGameOver.h"
#include "MenuLanguage.h"
#include "MenuMain.h"
#include "MenuInGame.h"

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>

MenuManager::MenuManager() :
    currentMenu(nullptr),
    changeState(false)
{
    // Defaults
    strings.play       = "";
    strings.difficulty = "";
    strings.language   = "";
    strings.quit       = "";
    strings.easy       = "";
    strings.normal     = "";
    strings.hard       = "";
}

void MenuManager::Init() {    
    SetLanguage(LangOpt::ENG);
    SetDifficulty(DiffOpt::EASY);
    SetMenu(MenuID::MAIN);
}

MenuManager::~MenuManager() {
    delete currentMenu;
    currentMenu = nullptr;
}

void MenuManager::SetMenu(MenuID ID) {
    delete currentMenu;
    currentMenu = nullptr;
    // Load new menu
    if (ID == MenuID::MAIN) {
        currentMenu = new MenuMain(
            vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 + 50),
            std::string("COLDLINE"));
    }
    else if (ID == MenuID::DIFF) {
        currentMenu = new MenuDifficulty(
            vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 + 50),
            strings.difficulty);
    }
    else if (ID == MenuID::LANG) {
        currentMenu = new MenuLanguage(
            vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 + 50),
            strings.language);
    }
    else if (ID == MenuID::INGAME) {
        currentMenu = new MenuInGame(
            vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 + 50),
            strings.pause);
    }
    else if (ID == MenuID::COMPLETE) {
        currentMenu = new MenuGameOver(
            vmake(SCR_WIDTH / 2 - 120, SCR_HEIGHT / 2 + 50),
            strings.levelComplete);
    }
    else if (ID == MenuID::GAMEOVER) {
        currentMenu = new MenuGameOver(
            vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 + 50),
            strings.gameOver);
    }
}

void MenuManager::ProcessInput(Action action) {
    if (currentMenu)
        currentMenu->ProcessInput(action);
}

void MenuManager::Run() {
    if (currentMenu)
        currentMenu->Run();
}

void MenuManager::Render() {
    if (currentMenu)
        currentMenu->Render();
}

void MenuManager::Quit() {
    exit(0);
}

void MenuManager::SetLanguage(LangOpt lang) {
    language = lang;

    // Read JSON
    FILE* fp = fopen("../data/lang.json", "rb"); // non-Windows use "r"
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document d;
    d.ParseStream(is);
    assert(d.IsObject());
    fclose(fp);

    // Parse
    if (language == LangOpt::ENG)
        ParseLanguage(d, "ENG");
    else if (language == LangOpt::ESP)
        ParseLanguage(d, "ESP");
    else if (language == LangOpt::CAT)
        ParseLanguage(d, "CAT");
}


void MenuManager::ParseLanguage(const rapidjson::Document &d, char* lang){
    assert(d.HasMember(lang));
    strings.play          = d[lang]["play"].GetString();
    strings.difficulty    = d[lang]["difficulty"].GetString();
    strings.language      = d[lang]["language"].GetString();
    strings.quit          = d[lang]["quit"].GetString();
    strings.easy          = d[lang]["easy"].GetString();
    strings.normal        = d[lang]["normal"].GetString();
    strings.hard          = d[lang]["hard"].GetString();
    strings.mainMenu      = d[lang]["mainMenu"].GetString();
    strings.pause         = d[lang]["pause"].GetString();
    strings.levelComplete = d[lang]["levelComplete"].GetString();
    strings.gameOver      = d[lang]["gameOver"].GetString();
    strings.close         = d[lang]["close"].GetString();
}