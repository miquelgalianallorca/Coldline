#pragma once

#include "stdafx.h"
#include "swalib\sys.h"
#include "swalib\core.h"
#include "Component.h"
#include "PhysicsEngine.h"

class  Entity;
struct Message;

class ComponentCollider : public Component {
public:
    ComponentCollider(Entity* _entity, 
        PhysicsEngine* _physicsEngine,
        PhysicsEngine::Collider _collider);
    void Run();
    void ReceiveMessage(Message *msg);

private:
	PhysicsEngine::Collider collider;
    PhysicsEngine *         physicsEngine;
    bool                    isActive;
};
