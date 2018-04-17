#pragma once

class Menu;

class MenuManager {
public:
    enum class MenuID { MAIN, DIFF, LANG, GAMEOVER, COMPLETE };
    enum class Action { LEFT, UP, RIGHT, DOWN, OK, BACK };

    enum class DiffOpt { EASY, NORMAL, HARD };
    enum class LangOpt { ENG,  ESP,    CAT };

    MenuManager();
    ~MenuManager();

    void SetMenu(MenuID ID);

    void ProcessInput(Action action);
    void Run();
    void Render();

    bool GetChangeState() const { return changeState; }
    void SetChangeState(bool value) { changeState = value; }
    
    DiffOpt GetDifficulty() const { return difficulty; }
    void SetDifficulty(DiffOpt diff) { difficulty = diff; }
    LangOpt GetLanguage() const { return language; }
    void SetLanguage(LangOpt lang) { language = lang; }

private:
    Menu* currentMenu;
    bool  changeState;

    DiffOpt difficulty;
    LangOpt language;
};
