#pragma once

#include "stdafx.h"
#include "swalib\sys.h"
#include "swalib\core.h"

class Entity {
public:
    Entity(vec2 _pos, float _vel, GLuint _gfx, float _radius, float _angle, bool _alive);

    vec2   GetPos();
    float  GetVel();
    GLuint GetGfx();
    float  GetRadius();
    float  GetAngle();
    bool   GetAlive();

    void SetPos  (vec2  _pos);
    void SetAngle(float _angle);
    void SetAlive(bool  _alive);

    virtual void Run()    = 0;
    virtual void Render() = 0;

protected:
    vec2   pos;
    float  vel;
    GLuint gfx;
    float  radius;
    float  angle;
    bool   alive;
};