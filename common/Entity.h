#pragma once

#include "stdafx.h"
#include "swalib\sys.h"
#include "swalib\core.h"

class Entity {
public:
    enum class EntityType{ PLAYER, ENEMY };

    Entity(vec2 _pos, float _vel, float _radius, float _angle, bool _alive);

    vec2   GetPos();
    float  GetVel();
    float  GetRadius();
    float  GetAngle();
    bool   GetAlive();
    EntityType GetType();

    void SetPos  (vec2  _pos);
    void SetAngle(float _angle);
    void SetAlive(bool  _alive);

    virtual void Run()    = 0;

protected:
    EntityType entityType;
    vec2       pos;
    float      vel;
    float      radius;
    float      angle;
    bool       alive;
};