#pragma once

#include "Component.h"

class  Entity;
struct Message;

class ComponentPlayer : public Component {
public:
    ComponentPlayer(Entity *_entity, float _range, int _attackTime);
    void Run();
    void ReceiveMessage(Message *msg);

private:
    float playerRange;
    bool  isAttacking;
    int   attackCounter;
    int   attackTime;
};
