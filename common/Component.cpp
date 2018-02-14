#include "Component.h"
#include "Message.h"

// Component ===================================================================
Component::Component(Entity *_entity) :
	entity(_entity)
{}

Component::~Component() {}
// =============================================================================

// Transform ===================================================================
ComponentTransform::ComponentTransform(Entity *_entity, vec2 _pos, float _radius, float _angle) :
	Component(_entity),
	pos(_pos),
	radius(_radius),
	angle(_angle)
{}

void ComponentTransform::ReceiveMessage(Message *msg) {
	if (auto moveMsg = dynamic_cast<MessageMove*>(msg)) {
		pos    = vadd(pos, moveMsg->amount);
		angle += moveMsg->angle;
	}
}
// ============================================================================

// Move =======================================================================
ComponentMove::ComponentMove(Entity *_entity, float _velocity) :
	Component(_entity),
	velocity(_velocity)
{}

void ComponentMove::Run() {
	//...
}
// ============================================================================