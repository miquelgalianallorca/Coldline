#pragma once

#include "Component.h"

class  Entity;
struct Message;

class ComponentPlayer : public Component {
public:
    ComponentPlayer(Entity *_entity, float _range, int _maxSlashTime);
    void Run();
    void ReceiveMessage(Message *msg);

private:
    float playerRange;
    int   slashTimer;
    int   maxSlashTime;
};