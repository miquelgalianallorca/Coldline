#pragma once

class Menu;

class MenuManager {
public:
    enum class MenuID { MAIN, DIFF, LANG, GAMEOVER, COMPLETE };
    enum class Action { LEFT, UP, RIGHT, DOWN, OK, BACK };

    MenuManager();
    ~MenuManager();

    void SetMenu(MenuID ID);

    void ProcessInput(Action action);
    void Run();
    void Render();

    bool GetChangeState() const { return changeState; }
    void SetChangeState(bool value) { changeState = value; }

private:
    Menu* currentMenu;
    bool  changeState;
};
