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
		GraphicsEngine *_graphicsEngine, bool _isVisible);
	void Run();
    virtual void ReceiveMessage(Message *msg);

private:
	GraphicsEngine::Drawable   drawable;
	GraphicsEngine*            graphicsEngine;

protected:
    bool isVisible;
};

class ComponentRenderableFX : public ComponentRenderable {
public:    
    ComponentRenderableFX(Entity *_entity, GraphicsEngine::Drawable _drawable,
        GraphicsEngine *_graphicsEngine, bool _isVisible) :
        ComponentRenderable(_entity, _drawable, _graphicsEngine, _isVisible)
    {}
    void ReceiveMessage(Message *msg);
};