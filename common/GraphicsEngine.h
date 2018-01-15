#pragma once

#include "stdafx.h"
#include "swalib\sys.h"
#include "swalib\core.h"

class GraphicsEngine {
public:
    enum class Sprite { PLAYER, ENEMY, FLOOR, SLASH, BLOOD, BULLET };
    
    GraphicsEngine();
    ~GraphicsEngine();

    void Draw(Sprite sprite, vec2 pos, vec2 size, float angle);

private:
    GLuint texPlayer;
    GLuint texFloor;
    GLuint texEnemy;
    GLuint texBlood;
    GLuint texSlash;
    GLuint texBullet;
};