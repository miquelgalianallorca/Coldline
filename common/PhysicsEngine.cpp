#include "PhysicsEngine.h"
#include <algorithm>

PhysicsEngine::PhysicsEngine() {}

PhysicsEngine::~PhysicsEngine() {}

void PhysicsEngine::RegisterCollider(Collider *collider) {
	registeredColliders.push_back(collider);
}

void PhysicsEngine::ClearColliders() {
    registeredColliders.clear();
}

void PhysicsEngine::Run() {
    for (auto collider : registeredColliders) {

    }
}
