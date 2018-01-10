#pragma once

#include "Entity.h"

class EntityEnemy : public Entity {
public:
    EntityEnemy(vec2 _pos, float _vel, GLuint _gfx, float _radius,
        float _angle, bool _alive, GLuint _gfxBlood);

    void Run();
    void Render();

private:
    GLuint gfxBlood;
};