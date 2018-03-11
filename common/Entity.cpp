#include "Entity.h"
#include "Game.h"
#include "Message.h"
#include "Component.h"

Entity::~Entity() {
    for (auto component : components)
        delete component;
    components.clear();
}

bool Entity::GetAlive()             { return alive;   }
void Entity::SetAlive(bool  _alive) { alive = _alive; }

void Entity::AddComponent(Component *component) {
	if (component) components.push_back(component);
}

void Entity::ReceiveMessage(Message *msg) {
    // Entity messages
    if (auto MSG = dynamic_cast<MessageSlashFX*>(msg))
        game->ReceiveMessage(msg);
    // Component messages
    for (auto component : components)
        component->ReceiveMessage(msg);
}

void Entity::Run() {
	for (auto component : components)
		component->Run();
}