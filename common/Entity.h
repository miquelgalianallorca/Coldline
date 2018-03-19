#pragma once

#include "stdafx.h"
#include "swalib\sys.h"
#include "swalib\core.h"

class  Component;
class  Game;
struct Message;

class Entity {
public:
    Entity(Game *_game) : game(_game), alive(true) {}
    ~Entity();

    bool GetAlive();
    void SetAlive(bool  _alive);
    
    void Run();

	void AddComponent(Component *component);
	void ReceiveMessage(Message *msg);

protected:
    bool alive;
	std::vector<Component*> components;
    Game *game;
};