#pragma once

#include "Entity.h"

class EntityPlayer : public Entity {
public:
    EntityPlayer(vec2 _pos, float _vel, GLuint _gfx, float _radius,
        float _angle, bool _alive, float _playerRange, GLuint _gfxSlash);

    void Run();
    void Render();

    void Move(vec2 newPos, float angle);
    void Attack();

private:
    GLuint gfxSlash;
    float  playerRange;
    int    slashTimer;
};