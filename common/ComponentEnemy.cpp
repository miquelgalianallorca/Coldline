#include "ComponentEnemy.h"
#include "ComponentRenderable.h"
#include "Entity.h"
#include "Message.h"

// Player ===============================================
ComponentEnemy::ComponentEnemy(Entity *_entity, size_t _timeToShoot) :
    Component(_entity),
    timeToShoot(_timeToShoot),
    shootTimer(0),
    isMovingRight(false)
{}

void ComponentEnemy::Run() {    
    // Transform ========================================
    MessageGetTransform* msg = new MessageGetTransform();
    entity->ReceiveMessage(msg);
    vec2 pos = msg->pos;
    float angle = msg->angle;
    delete msg;
    // ==================================================

    // Move =============================================
    if (pos.x < 0 || pos.x > 640)
        isMovingRight = !isMovingRight;

    MessageMove*     msgMove  = new MessageMove();
    MessageSetAngle* msgAngle = new MessageSetAngle();
    if (isMovingRight) {
        msgMove->direction = MessageMove::Dir::RIGHT;
        msgAngle->angle = 0.f;
    }
    else {
        msgMove->direction = MessageMove::Dir::LEFT;
        msgAngle->angle = 179.f;
    }
    entity->ReceiveMessage(msgMove);
    entity->ReceiveMessage(msgAngle);
    delete msgMove;
    delete msgAngle;
    // ==================================================

    // Shoot ============================================
    if (shootTimer < timeToShoot)
        ++shootTimer;
    else {
        // Shoot
        MessageEnemyShoot *msg = new MessageEnemyShoot(pos, angle);
        entity->ReceiveMessage(msg);
        delete msg;
        shootTimer = 0;
    }
    // ==================================================
}

void ComponentEnemy::ReceiveMessage(Message *msg) {}
// ======================================================
