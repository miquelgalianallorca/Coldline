#include "ComponentBullet.h"
#include "Entity.h"
#include "Message.h"

// Bullet ===============================================
ComponentBullet::ComponentBullet(Entity *_entity, float _angle) :
    Component(_entity),
    angle(_angle),
    lifeSpan(120)
{}

void ComponentBullet::Run() {
    // Automatic move
    MessageMove * msg = new MessageMove();
    MessageMove::Dir direction = MessageMove::Dir::DOWN;
    if (angle == 90.f)       direction = MessageMove::Dir::UP;
    else if (angle == -90.f) direction = MessageMove::Dir::DOWN;
    else if (angle == 179.f) direction = MessageMove::Dir::LEFT;
    else if (angle == 0.f)    direction = MessageMove::Dir::RIGHT;
    msg->direction = direction;
    entity->ReceiveMessage(msg);
    delete msg;

    // LifeSpan
    --lifeSpan;
    if (!lifeSpan) {
        MessageRemoveBullet* msg = new MessageRemoveBullet();
        entity->ReceiveMessage(new MessageRemoveBullet());
        delete msg;
    }
}

void ComponentBullet::ReceiveMessage(Message *msg) {}
// ======================================================
