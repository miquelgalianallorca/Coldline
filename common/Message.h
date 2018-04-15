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

struct MessageSetFXVisibility : public Message {
    MessageSetFXVisibility(bool _visibility) :
        visibility(_visibility) {}
    bool visibility;
};

struct MessageEnemyShoot : public Message {
    MessageEnemyShoot(vec2 _pos, float _angle) :
        pos(_pos),
        angle(_angle) {}
    vec2  pos;
    float angle;
};

struct MessageRemoveBullet : public Message {};
