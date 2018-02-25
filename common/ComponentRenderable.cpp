#include "ComponentRenderable.h"
#include "Message.h"

// Render =====================================================================
ComponentRenderable::ComponentRenderable(Entity *_entity, GraphicsEngine::Drawable _drawable,
	GraphicsEngine *_graphicsEngine) :
	Component(_entity),
	drawable(_drawable),
	graphicsEngine(_graphicsEngine)
{}

void ComponentRenderable::Run() {
	if (graphicsEngine) graphicsEngine->RegisterSprite(&drawable);
}

// ============================================================================