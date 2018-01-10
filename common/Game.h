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
    static float Distance(const vec2 &pos1, const vec2 &pos2);

private:
    // Game Utilities
    void LoadLevel(std::vector<Entity*> &enemies, GLuint texEnemy);

    // Textures
    GLuint texPlayer;
    GLuint texFloor;
    GLuint texEnemy;
    GLuint texBlood;
    GLuint texSlash;

    // Entities
    Entity *player;
    float playerRange;
    int slashTimer;
    std::vector<Entity*> enemies;

    // Level
    size_t numDead;
    bool   levelComplete;
};