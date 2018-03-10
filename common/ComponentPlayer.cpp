#include "ComponentPlayer.h"
#include "Message.h"

ComponentPlayer::ComponentPlayer(Entity *_entity,
    float _range, int _maxSlashTime) :
    Component(_entity),
    playerRange(_range),
    maxSlashTime(_maxSlashTime),
    slashTimer(_maxSlashTime)
{}

void ComponentPlayer::Run() {}

void ComponentPlayer::ReceiveMessage(Message *msg) {

}