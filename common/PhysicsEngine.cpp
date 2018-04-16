#include "PhysicsEngine.h"
#include "ComponentEnemy.h"
#include "Entity.h"
#include "Message.h"
#include <algorithm>

PhysicsEngine::PhysicsEngine() {}

PhysicsEngine::~PhysicsEngine() {}

void PhysicsEngine::RegisterCollider(Collider *collider) {
	registeredColliders.push_back(collider);
}

void PhysicsEngine::Clear() {
    registeredColliders.clear();
}

void PhysicsEngine::Run() {
    // Detect collisions Player/Bullet ==========================
    std::vector<Collider*> collidedColliders;
    for (auto collider1 : registeredColliders) {
        for (auto collider2 : registeredColliders) {
            if (collider1->ID == ColliderID::PLAYER &&
                collider2->ID == ColliderID::BULLET)
            {
                bool collision = IsColliding(*collider1, *collider2);
                if (collision) {
                    collidedColliders.push_back(collider1);
                    collidedColliders.push_back(collider2);
                }
            }
        }
    }
    // Remove duplicates
    collidedColliders.erase(std::unique(collidedColliders.begin(),
        collidedColliders.end()), collidedColliders.end());
    // Inform entity of collision
    for (auto collider : collidedColliders) {
        MessageCollisionBulletPlayer* msg = 
            new MessageCollisionBulletPlayer();
        collider->owner->ReceiveMessage(msg);
        delete msg;
    }
    // Clear
    collidedColliders.clear();
    // ==========================================================
    // Detect collisions Player/Enemy ===========================
    for (auto collider1 : registeredColliders) {
        for (auto collider2 : registeredColliders) {
            if (collider1->ID == ColliderID::PLAYER &&
                collider2->ID == ColliderID::ENEMY)
            {
                bool collision = IsColliding(*collider1, *collider2);
                if (collision) {
                    collidedColliders.push_back(collider1);
                    collidedColliders.push_back(collider2);
                }
            }
        }
    }
    // Remove duplicates (leave only enemies)
    collidedColliders.erase(std::remove_if(collidedColliders.begin(),
        collidedColliders.end(),
        [](Collider* col) { return col->ID == ColliderID::PLAYER; }),
        collidedColliders.end());
    // Inform entity of collision
    for (auto collider : collidedColliders) {
        MessageKillEnemy* msg = new MessageKillEnemy();
        msg->pos = collider->pos;
        collider->owner->ReceiveMessage(msg);
        delete msg;
    }
    // Clear
    collidedColliders.clear();
    // ==========================================================
}

bool PhysicsEngine::IsColliding(const Collider &collider1,
    const Collider &collider2)
{
    float dist = vlen(vsub(collider2.pos, collider1.pos));
    float collisionDist = collider1.radius + collider2.radius;
    if (dist > collisionDist) return false;
    else                      return true;
}