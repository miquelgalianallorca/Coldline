#include "ComponentRenderable.h"
#include "Message.h"

// Render =====================================================================
ComponentRenderable::ComponentRenderable(Entity *_entity, GraphicsEngine::Drawable _drawable,
	GraphicsEngine *_graphicsEngine, bool _isVisible) :
	Component(_entity),
	drawable(_drawable),
	graphicsEngine(_graphicsEngine),
    isVisible(_isVisible)
{}

void ComponentRenderable::Run() {
	if (graphicsEngine && isVisible)
        graphicsEngine->RegisterSprite(&drawable);
}

void ComponentRenderable::ReceiveMessage(Message *msg) {
    if (auto MSG = dynamic_cast<MessageUpdateDrawable*>(msg)) {
        drawable.angle = MSG->angle;
        drawable.pos   = MSG->pos;
    }
}
// ============================================================================

void ComponentRenderableFX::ReceiveMessage(Message *msg) {
    ComponentRenderable::ReceiveMessage(msg);
    if (auto MSG = dynamic_cast<MessageSetFXVisibility*>(msg)) {
        isVisible = MSG->visibility;
    }
}
