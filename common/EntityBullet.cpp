#include "EntityBullet.h"

EntityBullet::EntityBullet(vec2 _pos, float _vel, float _radius, float _angle, bool _alive) :
    Entity(nullptr)
    //Entity(_pos, _vel, _radius, _angle, _alive)
{
    //entityType = EntityType::BULLET;
}

void EntityBullet::Run() {
    //if      (angle ==   0.f) pos = vmake(pos.x + vel, pos.y);
    //else if (angle ==  90.f) pos = vmake(pos.x, pos.y + vel);
    //else if (angle == -90.f) pos = vmake(pos.x, pos.y - vel);
    //else if (angle == 179.f) pos = vmake(pos.x - vel, pos.y);
    //// Out of screen: delete bullet
    //if (pos.x < 0 || pos.x > SCR_WIDTH || pos.y < 0 || pos.y > SCR_HEIGHT)
    //    alive = false;
}