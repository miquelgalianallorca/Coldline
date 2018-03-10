#pragma once

#include "stdafx.h"
#include "swalib\sys.h"
#include "swalib\core.h"

class  Component;
struct Message;

class Entity {
public:
    Entity() {}
    ~Entity();

    bool GetAlive();
    void SetAlive(bool  _alive);
    
    void Run();

	void AddComponent(Component *component);
	void ReceiveMessage(Message *msg);

protected:
    bool alive;
	std::vector<Component*> components;
};