#pragma once

#include "Component.h"

class  Entity;
struct Message;

class ComponentEnemy : public Component {
public:
    ComponentEnemy(Entity *_entity, size_t _timeToShoot,
        vec2 _pos, float _angle);
    void Run();
    void ReceiveMessage(Message *msg);

private:
    vec2   pos;
    float  angle;
    size_t timeToShoot;
    size_t shootTimer;
};
