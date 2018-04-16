#pragma once

#include "stdafx.h"
#include "swalib\sys.h"
#include "swalib\core.h"

class PhysicsEngine {
public:
    enum class ColliderID { ENEMY, PLAYER, BULLET };
    struct Collider {
        Collider(vec2 _pos, float _radius,
            ColliderID _ID) :
            pos(_pos),
            radius(_radius),
            ID(_ID)
        {}
        vec2       pos;
        float      radius;
        ColliderID ID;
	};

    PhysicsEngine();
    ~PhysicsEngine();

	void RegisterCollider(Collider *collider);
	void ClearColliders();
    
    void Run();

private:
    std::vector<Collider*> registeredColliders;
};