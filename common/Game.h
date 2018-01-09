#pragma once

#include "stdafx.h"
#include "swalib\sys.h"
#include "swalib\core.h"
#include "swalib\font.h"

struct Entity {
    vec2   pos;
    float  vel;
    GLuint gfx;
    float  radius;
    float  angle;
    bool   alive;
};

// Game Utilities
void LoadLevel(std::vector<Entity> &enemies, GLuint texEnemy);
float Distance(const vec2 &pos1, const vec2 &pos2);

class Game {
public:
    Game();
    ~Game();

    void Run();
    void Render();

private:
    // Textures
    GLuint texPlayer;
    GLuint texFloor;
    GLuint texEnemy;
    GLuint texBlood;
    GLuint texSlash;

    // Entities
    Entity player;
    float playerRange = 50.f;
    int slashTimer = 0;
    std::vector<Entity> bullets;
    std::vector<Entity> enemies;
};