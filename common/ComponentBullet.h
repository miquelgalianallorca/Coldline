#pragma once

#include "Component.h"

class  Entity;
struct Message;

class ComponentBullet : public Component {
public:
    ComponentBullet(Entity *_entity, float _angle);

    void Run();
    void ReceiveMessage(Message *msg);

private:
    float  angle;
    size_t lifeSpan;
};
