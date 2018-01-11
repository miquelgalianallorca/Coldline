#include "EntityEnemy.h"

EntityEnemy::EntityEnemy(vec2 _pos, float _vel, GLuint _gfx, float _radius, float _angle, bool _alive,
    GLuint _gfxBlood) :
    Entity(_pos, _vel, _gfx, _radius, _angle, _alive),
    gfxBlood(_gfxBlood)
{
    entityType = EntityType::ENEMY;
}

void EntityEnemy::Run() {

}

void EntityEnemy::Render() {
    if (alive) CORE_RenderCenteredRotatedSprite(pos, vmake(radius * 2.f, radius * 2.f), angle, gfx);
    else       CORE_RenderCenteredRotatedSprite(pos, vmake(radius * 2.f, radius * 2.f), angle, gfxBlood);
}