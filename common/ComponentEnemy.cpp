#include "ComponentEnemy.h"
#include "ComponentRenderable.h"
#include "Entity.h"
#include "Message.h"

// Player ===============================================
ComponentEnemy::ComponentEnemy(Entity *_entity,
    size_t _timeToShoot, vec2 _pos, float _angle, float _speed) :
    Component(_entity),
    timeToShoot(_timeToShoot),
    pos(_pos),
    angle(_angle),
    shootTimer(0),
    speed(_speed),
    isMovingRight(false)
{}

void ComponentEnemy::Run() {    
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

void ComponentEnemy::ReceiveMessage(Message *msg) {
    if (auto MSG = dynamic_cast<MessageMove*>(msg)) {
        switch (MSG->direction) {
        case MessageMove::Dir::UP:
            pos = vadd(pos, vmake(0, speed));
            break;
        case MessageMove::Dir::DOWN:
            pos = vadd(pos, vmake(0, -speed));
            break;
        case MessageMove::Dir::LEFT:
            pos = vadd(pos, vmake(-speed, 0));
            break;
        case MessageMove::Dir::RIGHT:
            pos = vadd(pos, vmake(speed, 0));
            break;
        }
    }
    if (auto MSG = dynamic_cast<MessageSetAngle*>(msg)) {
        angle = MSG->angle;
    }
}
// ======================================================
