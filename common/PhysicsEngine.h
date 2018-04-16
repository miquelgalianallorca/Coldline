#pragma once

#include "stdafx.h"
#include "swalib\sys.h"
#include "swalib\core.h"

class Entity;

class PhysicsEngine {
public:
    enum class ColliderID { ENEMY, PLAYER, BULLET };
    struct Collider {
        Collider(vec2 _pos, float _radius,
            ColliderID _ID, Entity* _owner) :
            pos(_pos),
            radius(_radius),
            ID(_ID),
            owner(_owner)
        {}
        vec2       pos;
        float      radius;
        ColliderID ID;
        Entity*    owner;
	};

    PhysicsEngine();
    ~PhysicsEngine();

	void RegisterCollider(Collider *collider);
	void Clear();
    
    void Run();

private:
    std::vector<Collider*> registeredColliders;
    
    bool IsColliding(const Collider &collider1,
        const Collider &collider2);
};