#pragma once

#include "Entity.h"

class EntityPlayer : public Entity {
public:
    EntityPlayer(vec2 _pos, float _vel, float _radius,
        float _angle, bool _alive, float _playerRange);

    void Run();

    void Move(vec2 newPos, float angle);
    void Attack();

private:
    float  playerRange;
    int    slashTimer;
};