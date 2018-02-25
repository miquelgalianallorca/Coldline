#pragma once

#include "stdafx.h"
#include "swalib\sys.h"
#include "swalib\core.h"

struct Message {
	virtual ~Message() = 0 {}
};

struct MessageMove : public Message {
	vec2  amount;
};

struct MessageSetAngle : public Message {
	float angle;
};
