#pragma once

#include "Component.h"

class  Entity;
struct Message;

class ComponentEnemy : public Component {
public:
    ComponentEnemy(Entity *_entity, size_t _timeToShoot);
    void Run();
    void ReceiveMessage(Message *msg);

private:
    size_t timeToShoot;
    size_t shootTimer;

    bool isMovingRight;
};
