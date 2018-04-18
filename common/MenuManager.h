#pragma once

#include <string>

class Menu;

class MenuManager {
public:
    struct MenuStrings{
        std::string play;
        std::string difficulty;
        std::string language;
        std::string quit;
        std::string easy;
        std::string normal;
        std::string hard;
    };
    MenuStrings strings;

    enum class MenuID { MAIN, DIFF, LANG, GAMEOVER, COMPLETE };
    enum class Action { LEFT, UP, RIGHT, DOWN, OK, BACK };

    enum class DiffOpt { EASY, NORMAL, HARD };
    enum class LangOpt { ENG,  ESP,    CAT };

    MenuManager();
    ~MenuManager();

    void Init();
    void SetMenu(MenuID ID);
    void Quit();

    void ProcessInput(Action action);
    void Run();
    void Render();

    bool GetChangeState() const { return changeState; }
    void SetChangeState(bool value) { changeState = value; }
    
    DiffOpt GetDifficulty() const { return difficulty; }
    void SetDifficulty(DiffOpt diff) { difficulty = diff; }
    LangOpt GetLanguage() const { return language; }
    void SetLanguage(LangOpt lang);

private:
    Menu* currentMenu;
    bool  changeState;

    DiffOpt difficulty;
    LangOpt language;
};
