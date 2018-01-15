#include "EntityEnemy.h"
#include "globals.h"
#include "Game.h"

EntityEnemy::EntityEnemy(vec2 _pos, float _vel, float _radius, float _angle, bool _alive, int _timeToShoot) :
    Entity(_pos, _vel, _radius, _angle, _alive),
    timeToShoot(_timeToShoot),
    shootTimer(0)
{
    entityType = EntityType::ENEMY;
}

void EntityEnemy::Run() {
    if (shootTimer < timeToShoot) ++shootTimer;
    else {
        // Shoot
        /*Game::Direction dir;
        if      (angle == 90.f)  dir = Game::Direction::UP;
        else if (angle == -90.f) dir = Game::Direction::DOWN;
        else if (angle == 179.f) dir = Game::Direction::LEFT;
        else                     dir = Game::Direction::RIGHT;*/
        game->AddBullet(pos, angle);
        shootTimer = 0;
    }
}