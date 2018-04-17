#pragma once

#include "GameState.h"
#include "GameInputManager.h"

class GameStatePlay : public GameState {
public:
	enum class Difficulty { EASY, NORMAL, HARD };
    GameStatePlay(Difficulty diff);
    ~GameStatePlay();

    void Input();
    void Run();
    void Render();

private:
    GameInputManager inputManager;
};