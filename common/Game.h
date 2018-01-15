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
    enum class Direction { LEFT, UP, RIGHT, DOWN };

    Game();
    ~Game();

    void  Run();
    void  Render();
    bool  IsLevelComplete();
    float Distance(const vec2 &pos1, const vec2 &pos2);
    void  CheckKill(const vec2& playerPos, const float playerRange);
    void  ProcessInput(Action action);
    void  SetSlashing(bool value);
    void  AddBullet(vec2 pos, float angle);

private:
    // Game Utilities
    void LoadLevel();

    // Entities
    std::vector<Entity*> entities;
    std::vector<Entity*> enemies;  // Only refs
    std::vector<Entity*> bullets;  // Only refs
    EntityPlayer *player;          // Only refs

    // Level
    size_t numDead;
    bool   levelComplete;
    bool   playerSlashing;

    GraphicsEngine graphicsEngine;
};