#pragma once

#include "stdafx.h"
#include "swalib\sys.h"
#include "swalib\core.h"
#include "GraphicsEngine.h"

class  Entity;
struct Message;

class Component {
public:
	virtual ~Component() = 0;
	
	virtual void Run()                        {}
	virtual void ReceiveMessage(Message *msg) {}

protected:
	Component(Entity *_entity);

private:
	Entity *entity;
};

class ComponentTransform : public Component {
public:
	ComponentTransform(Entity *_entity, vec2 _pos, float _radius, float _angle);
	
	void ReceiveMessage(Message *msg);

	vec2  GetPos()    const { return pos;    }
	float GetRadius() const { return radius; }
	float GetAngle()  const { return angle;  }

private:
	vec2  pos;
	float radius;
	float angle;
};

class ComponentMove : public Component {
public:
	ComponentMove(Entity *_entity, float _velocity);
	
	float GetVelocity() const { return velocity; }

private:
	float velocity;
};

class ComponentRenderable : public Component {
public:	
	ComponentRenderable(Entity *_entity, GraphicsEngine::Drawable _drawable,
		GraphicsEngine *_graphicsEngine);
	void Run();

private:
	GraphicsEngine::Drawable   drawable;
	GraphicsEngine*            graphicsEngine;
};