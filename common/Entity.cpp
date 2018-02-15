#include "Entity.h"
#include "Component.h"

Entity::Entity(vec2 _pos, float _vel, float _radius, float _angle, bool _alive) :
    //pos(_pos),
    //vel(_vel),
    //radius(_radius),
    //angle(_angle),
    alive(_alive)
{}

//vec2  Entity::GetPos()    { return pos;    }
//float Entity::GetVel()    { return vel;    }
//float Entity::GetRadius() { return radius; }
//float Entity::GetAngle()  { return angle;  }
bool  Entity::GetAlive()  { return alive;  }

//Entity::EntityType Entity::GetType() { return entityType; }
//
//void Entity::SetPos  (vec2 _pos)    { pos   = _pos;   }
//void Entity::SetAngle(float _angle) { angle = _angle; }
void Entity::SetAlive(bool  _alive) { alive = _alive; }

void Entity::AddComponent(Component *component) {
	if (component) components.push_back(component);
}

void Entity::ReceiveMessage(Message *msg) {
	for (auto component : components)
		component->ReceiveMessage(msg);
}

void Entity::Run() {
	for (auto component : components)
		component->Run();
}