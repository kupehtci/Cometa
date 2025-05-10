//
// Created by Daniel Laplana Gimeno on 7/5/25.
//

#ifndef COMETA_COLLISION_H
#define COMETA_COLLISION_H

#include "world/Components.h"
#include "physics/CollisionDispatcher.h"

/**
 * Represents a collision between two colliders
 * It stores the two colliders involved in the collision and the calculated CollisionPoint.
 */
struct Collision {
    ColliderComponent* colliderCompA = nullptr;
    ColliderComponent* colliderCompB = nullptr;
    CollisionPoint point{};

    Collision(ColliderComponent* colliderA, ColliderComponent* colliderB, CollisionPoint point)
        : colliderCompA(colliderA), colliderCompB(colliderB), point(point) {}
};

#endif //COMETA_COLLISION_H
