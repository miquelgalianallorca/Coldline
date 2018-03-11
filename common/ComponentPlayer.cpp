#include "ComponentPlayer.h"
#include "ComponentRenderable.h"
#include "Entity.h"
#include "Message.h"

// Player ===============================================
ComponentPlayer::ComponentPlayer(Entity *_entity, float _range) :
    Component(_entity),
    playerRange(_range)
{}

void ComponentPlayer::Run() {}

void ComponentPlayer::ReceiveMessage(Message *msg) {
    if (auto MSG = dynamic_cast<MessageAttack*>(msg)) {
        MessageSlashFX *msgSlash = new MessageSlashFX();
        entity->ReceiveMessage(msgSlash);
        delete msgSlash;
    }
}
// ======================================================

// Slash ================================================
void ComponentSlash::Run() {
    if (slashTimer > 0) --slashTimer;
}

void ComponentSlash::ReceiveMessage(Message *msg) {

}
// ======================================================