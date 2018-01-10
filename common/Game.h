#pragma once

#include "stdafx.h"
#include "swalib\sys.h"
#include "swalib\core.h"
#include "swalib\font.h"

class Entity;

// Game Utilities
void LoadLevel(std::vector<Entity> &enemies, GLuint texEnemy);
float Distance(const vec2 &pos1, const vec2 &pos2);

class Game {
public:
    Game();
    ~Game();

    void Run();
    void Render();
    bool IsLevelComplete();

private:
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
    //std::vector<Entity> bullets;
    std::vector<Entity*> enemies;

    // Level
    size_t numDead;
    bool   levelComplete;
};