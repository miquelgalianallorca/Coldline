#include "Entity.h"


Entity::Entity(vec2 _pos, float _vel, GLuint _gfx, float _radius, float _angle, bool _alive) :
    pos(_pos),
    vel(_vel),
    gfx(_gfx),
    radius(_radius),
    angle(_angle),
    alive(_alive)
{}

vec2   Entity::GetPos()    { return pos;    }
float  Entity::GetVel()    { return vel;    }
GLuint Entity::GetGfx()    { return gfx;    }
float  Entity::GetRadius() { return radius; }
float  Entity::GetAngle()  { return angle;  }
bool   Entity::GetAlive()  { return alive;  }

void Entity::SetPos  (vec2 _pos)    { pos   = _pos;   }
void Entity::SetAngle(float _angle) { angle = _angle; }
void Entity::SetAlive(bool  _alive) { alive = _alive; }