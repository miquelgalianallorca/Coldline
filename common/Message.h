#pragma once

#include "stdafx.h"
#include "swalib\sys.h"
#include "swalib\core.h"

struct Message {
	virtual ~Message() = 0 {}
};

struct MessageMove : public Message {
	enum class Dir { UP, DOWN, LEFT, RIGHT };
    Dir direction;
};

struct MessageSetAngle : public Message {
	float angle;
};

struct MessageAttack : public Message {};

struct MessageUpdateDrawable : public Message {
    vec2  pos;
    float angle;
};