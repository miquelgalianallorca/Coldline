#include "ComponentCollider.h"
#include "Message.h"

// Collisions ====================================================
ComponentCollider::ComponentCollider(Entity *_entity,
    PhysicsEngine *_physicsEngine,
    PhysicsEngine::Collider _collider) :
    Component(_entity),
    physicsEngine(_physicsEngine),
    collider(_collider),
    isActive(true)
{}

void ComponentCollider::Run() {
	if (physicsEngine && isActive) {
        physicsEngine->RegisterCollider(&collider);
    }
}

void ComponentCollider::ReceiveMessage(Message *msg) {
    /*if (auto MSG = dynamic_cast<MessageUpdateDrawable*>(msg)) {
        drawable.angle = MSG->angle;
        drawable.pos   = MSG->pos;
    }*/
}
// ============================================================================
