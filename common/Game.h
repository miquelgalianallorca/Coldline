#pragma once

#include "stdafx.h"
#include "swalib\sys.h"
#include "swalib\core.h"
#include "swalib\font.h"

class Entity;

class Game {
public:
    Game();
    ~Game();

    void Run();
    void Render();
    bool IsLevelComplete();
    float Distance(const vec2 &pos1, const vec2 &pos2);

    void CheckKill(const vec2& playerPos, const float playerRange);

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

    // Level
    size_t numDead;
    bool   levelComplete;
};