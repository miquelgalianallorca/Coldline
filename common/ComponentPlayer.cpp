#include "ComponentPlayer.h"
#include "ComponentEnemy.h"
#include "ComponentRenderable.h"
#include "Entity.h"
#include "Message.h"

// Player ===============================================
ComponentPlayer::ComponentPlayer(Entity *_entity, float _range,
    int _attackTime) :
    Component(_entity),
    playerRange(_range),
    isAttacking(false),
    attackCounter(0),
    attackTime(_attackTime)
{}

void ComponentPlayer::Run() {
    if (isAttacking) {
        --attackCounter;
        if (attackCounter == 0) {
            isAttacking = false;
            MessageSetFXVisibility *msgVis =
                new MessageSetFXVisibility(false);
            entity->ReceiveMessage(msgVis);
            delete msgVis;
        }
    }
}

void ComponentPlayer::ReceiveMessage(Message *msg) {
    if (auto MSG = dynamic_cast<MessageAttack*>(msg)) {
        attackCounter = attackTime;
        isAttacking   = true;
        MessageSetFXVisibility *msgVis = 
            new MessageSetFXVisibility(true);
        entity->ReceiveMessage(msgVis);
        delete msgVis;
    }
    else if (auto MSG = dynamic_cast<MessageCollisionBulletPlayer*>(msg)) {
        MessageKillPlayer* msgKill = new MessageKillPlayer();
        entity->ReceiveMessage(msgKill);
        delete msgKill;
    }
}
// ======================================================
