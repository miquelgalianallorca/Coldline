#pragma once

#include "stdafx.h"
#include "swalib\sys.h"
#include "swalib\core.h"
#include "GraphicsEngine.h"
#include "Component.h"

class  Entity;
struct Message;

class ComponentRenderable : public Component {
public:	
	ComponentRenderable(Entity *_entity, GraphicsEngine::Drawable _drawable,
		GraphicsEngine *_graphicsEngine);
	void Run();

private:
	GraphicsEngine::Drawable   drawable;
	GraphicsEngine*            graphicsEngine;
};