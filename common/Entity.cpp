#include "Entity.h"
#include "Game.h"
#include "Message.h"
#include "Component.h"

#include "swalib\sys.h"
#include "swalib\core.h"

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
    // Entity only messages ===================================
    if (auto MSG = dynamic_cast<MessageEnemyShoot*>(msg)) {
        game->AddBullet(MSG->pos, MSG->angle);
    }
    else if (auto MSG = dynamic_cast<MessageDeleteEntity*>(msg)) {
        game->DeleteEntity(this);
    }
    else if (auto MSG = dynamic_cast<MessageKillPlayer*>(msg)) {
        game->KillPlayer();
    }
    else if (auto MSG = dynamic_cast<MessageKillEnemy*>(msg)) {
        game->KillEnemy(this, MSG->pos);
    }
    // ========================================================
    // Component messages =====================================
    for (auto component : components)
        component->ReceiveMessage(msg);
    // ========================================================
}

void Entity::Run() {
	for (auto component : components)
		component->Run();
}