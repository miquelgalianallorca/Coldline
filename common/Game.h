#pragma once

#include "stdafx.h"
#include "swalib\sys.h"
#include "swalib\core.h"
#include "swalib\font.h"

#include "GraphicsEngine.h"

class Entity;
class EntityPlayer;

class Game {
public:
    enum class Action { MOVE_L, MOVE_U, MOVE_R, MOVE_D, SLASH };

    Game();
    ~Game();

    void  Run();
    void  Render();
    bool  IsLevelComplete();
    float Distance(const vec2 &pos1, const vec2 &pos2);
    void  CheckKill(const vec2& playerPos, const float playerRange);
    void  ProcessInput(Action action);

private:
    // Game Utilities
    void LoadLevel();

    // Textures
    GLuint texPlayer;
    GLuint texFloor;
    GLuint texEnemy;
    GLuint texBlood;
    GLuint texSlash;

    std::vector<Entity*> entities;
    EntityPlayer *player;

    // Level
    size_t numDead;
    bool   levelComplete;

    GraphicsEngine graphicsEngine;
};