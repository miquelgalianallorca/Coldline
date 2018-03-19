#pragma once

#include "stdafx.h"
#include "swalib\sys.h"
#include "swalib\core.h"

struct Message {
	virtual ~Message() = 0 {}
};

// Component to Component =======================
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
// ==============================================

// Component to Entity ==========================
struct MessageAddSlash : public Message {};

struct MessageSlashFX : public Message {
	vec2  pos;
	float angle;
	vec2  size;
};
// ==============================================