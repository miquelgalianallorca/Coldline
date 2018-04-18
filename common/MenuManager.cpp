#include "MenuManager.h"
#include "stdafx.h"
#include "MenuDifficulty.h"
#include "MenuLanguage.h"
#include "MenuMain.h"
#include "MenuInGame.h"

#include "rapidjson\document.h"
#include "rapidjson\filereadstream.h"
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
            std::string("PAUSE"));
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
    if (language == LangOpt::ENG) {
        assert(d.HasMember("ENG"));
        strings.play       = d["ENG"]["play"].GetString();
        strings.difficulty = d["ENG"]["difficulty"].GetString();
        strings.language   = d["ENG"]["language"].GetString();
        strings.quit       = d["ENG"]["quit"].GetString();
        strings.easy       = d["ENG"]["easy"].GetString();
        strings.normal     = d["ENG"]["normal"].GetString();
        strings.hard       = d["ENG"]["hard"].GetString();
    }
    else if (language == LangOpt::ESP) {
        assert(d.HasMember("ESP"));
        strings.play       = d["ESP"]["play"].GetString();
        strings.difficulty = d["ESP"]["difficulty"].GetString();
        strings.language   = d["ESP"]["language"].GetString();
        strings.quit       = d["ESP"]["quit"].GetString();
        strings.easy       = d["ESP"]["easy"].GetString();
        strings.normal     = d["ESP"]["normal"].GetString();
        strings.hard       = d["ESP"]["hard"].GetString();
    }
    else if (language == LangOpt::CAT) {
        assert(d.HasMember("CAT"));
        strings.play       = d["CAT"]["play"].GetString();
        strings.difficulty = d["CAT"]["difficulty"].GetString();
        strings.language   = d["CAT"]["language"].GetString();
        strings.quit       = d["CAT"]["quit"].GetString();
        strings.easy       = d["CAT"]["easy"].GetString();
        strings.normal     = d["CAT"]["normal"].GetString();
        strings.hard       = d["CAT"]["hard"].GetString();
    }
}