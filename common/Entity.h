#pragma once

#include "stdafx.h"
#include "swalib\sys.h"
#include "swalib\core.h"

class  Component;
struct Message;

class Entity {
public:
    enum class EntityType{ PLAYER, ENEMY, BULLET };

    Entity(vec2 _pos, float _vel, float _radius, float _angle, bool _alive);
	Entity() {}

    /*vec2       GetPos();
    float      GetVel();
    float      GetRadius();
    float      GetAngle();
	EntityType GetType();*/
    bool       GetAlive();

    /*void SetPos  (vec2  _pos);
    void SetAngle(float _angle);*/
    void SetAlive(bool  _alive);

    //virtual void Run() = 0; // Delete this
	void Run();             // ECS

	void AddComponent(Component *component);
	void ReceiveMessage(Message *msg);

protected:
   /* EntityType entityType;
    vec2       pos;
    float      vel;
    float      radius;
    float      angle;*/
    bool       alive;

	std::vector<Component*> components;
};