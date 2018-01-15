#pragma once

#include "Entity.h"

class EntityBullet : public Entity {
public:
    EntityBullet(vec2 _pos, float _vel, float _radius, float _angle, bool _alive);

    void Run();
};