#pragma once

#include "Component.h"

class  Entity;
struct Message;

class ComponentBullet : public Component {
public:
    ComponentBullet(Entity *_entity, float _angle) :
        Component(_entity),
        angle(_angle)
    {}
    void Run();
    void ReceiveMessage(Message *msg);

private:
    float angle;
};
