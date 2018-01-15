#include "EntityBullet.h"

EntityBullet::EntityBullet(vec2 _pos, float _vel, float _radius, float _angle, bool _alive) :
    Entity(_pos, _vel, _radius, _angle, _alive)
{
    entityType = EntityType::BULLET;
}

void EntityBullet::Run() {
    
}