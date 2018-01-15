#pragma once

#include "Entity.h"

class EntityEnemy : public Entity {
public:
    EntityEnemy(vec2 _pos, float _vel, float _radius,
        float _angle, bool _alive);

    void Run();
};