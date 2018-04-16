#include "ComponentEnemy.h"
#include "ComponentRenderable.h"
#include "Entity.h"
#include "Message.h"

// Player ===============================================
ComponentEnemy::ComponentEnemy(Entity *_entity,
    size_t _timeToShoot, vec2 _pos, float _angle) :
    Component(_entity),
    timeToShoot(_timeToShoot),
    pos(_pos),
    angle(_angle),
    shootTimer(0)
{}

void ComponentEnemy::Run() {
    if (shootTimer < timeToShoot)
        ++shootTimer;
    else {
        // Shoot
        MessageEnemyShoot *msg = new MessageEnemyShoot(pos, angle);
        entity->ReceiveMessage(msg);
        delete msg;
        shootTimer = 0;
    }
}

void ComponentEnemy::ReceiveMessage(Message *msg) {}
// ======================================================
