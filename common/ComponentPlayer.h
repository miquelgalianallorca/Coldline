#pragma once

#include "Component.h"

class  Entity;
struct Message;

class ComponentPlayer : public Component {
public:
    ComponentPlayer(Entity *_entity, float _range);
    void Run();
    void ReceiveMessage(Message *msg);

private:
    float playerRange;
};

class ComponentSlash : public Component {
public:
    ComponentSlash(Entity *_entity) : Component(_entity) {}
    void Run();
    void ReceiveMessage(Message *msg);

private:
    int slashTimer;
    int maxSlashTime;
};