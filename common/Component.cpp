#include "Component.h"
#include "Entity.h"
#include "Message.h"

// Component ===================================================================
Component::Component(Entity *_entity) :
	entity(_entity)
{}

Component::~Component() {}
// =============================================================================

// Transform ===================================================================
ComponentTransform::ComponentTransform(Entity *_entity, vec2 _pos,
    float _radius, float _angle, float _speed, bool _canExitScreen) :
	Component(_entity),
	pos(_pos),
	radius(_radius),
	angle(_angle),
    speed(_speed),
    canExitScreen(_canExitScreen)
{}

void ComponentTransform::ReceiveMessage(Message *msg) {
	if (auto MSG = dynamic_cast<MessageMove*>(msg)) {
		switch (MSG->direction) {
            case MessageMove::Dir::UP:
                pos = vadd(pos, vmake(0, speed));
                break;
            case MessageMove::Dir::DOWN:
                pos = vadd(pos, vmake(0, -speed));
                break;
            case MessageMove::Dir::LEFT:
                pos = vadd(pos, vmake(-speed, 0));
                break;
            case MessageMove::Dir::RIGHT:
                pos = vadd(pos, vmake(speed, 0));
                break;
        }
        if (!canExitScreen) pos = ClampPos(pos);
        UpdateGraphics();
    }
	if (auto MSG = dynamic_cast<MessageSetAngle*>(msg)) {
		angle = MSG->angle;
        UpdateGraphics();
    }
}

void ComponentTransform::UpdateGraphics() {
    MessageUpdateDrawable *updateDrawableMsg = new MessageUpdateDrawable();
    updateDrawableMsg->angle = angle;
    updateDrawableMsg->pos   = pos;
    entity->ReceiveMessage(updateDrawableMsg);
    delete updateDrawableMsg;
}

vec2 ComponentTransform::ClampPos(vec2 pos) {
    if (pos.x > SCR_WIDTH - radius) pos.x = SCR_WIDTH - radius;
    else if (pos.x < radius) pos.x = radius;
    if (pos.y > SCR_HEIGHT - radius) pos.y = SCR_HEIGHT - radius;
    else if (pos.y < radius) pos.y = radius;
    return pos;
}
// ============================================================================
