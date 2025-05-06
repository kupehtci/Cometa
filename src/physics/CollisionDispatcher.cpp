//
// Created by Daniel Laplana Gimeno on 6/5/25.
//

#include "CollisionDispatcher.h"

#include <complex>

#include "physics/Collider.h"
#include "physics/Collider.h"
#include "world/Components.h"

#include <iostream>

CollisionPoint CollisionDispatcher::IntersectBoxSphere(const Collider* collider, const Transform* transform, const Collider* otherCollider, const Transform* otherTransform)
{
    std::cout << "Collision detected Box sphere" << std::endl;
    return {};
}

CollisionPoint CollisionDispatcher::IntersectSphereSphere(const Collider* collider, const Transform* transform, const Collider* otherCollider, const Transform* otherTransform)
{
    std::cout << "Collision detected sphere sphere" << std::endl;
    const SphereCollider* a = static_cast<const SphereCollider* >(collider);
    const SphereCollider* b = static_cast<const SphereCollider* >(otherCollider);

    glm::vec3 centerA = transform->position + a->GetCenter();
    glm::vec3 centerB = otherTransform->position + b->GetCenter();

    glm::vec3 del = centerB - centerA;
    glm::vec3 norm = glm::normalize(del);

    float distance = glm::length(del);
    float radiusSum = a->GetRadius() + b->GetRadius();

    CollisionPoint point{};

    point.a = centerA + (norm * a->GetRadius());
    point.b = centerB - (norm * b->GetRadius());
    point.normal = norm;
    point.length = (radiusSum) - distance;
    point.collided = (distance < radiusSum);

    // std::cout << "Collider a radius" << a->GetRadius() << " collider B radius: " << b->GetRadius() << std::endl;
    // std::cout << "Point: (" << point.a.x << ", " << point.a.y << ", " << point.a.z << ") has collided: " << point.collided << std::endl;
    return point;
    return {};
}

CollisionPoint CollisionDispatcher::IntersectBoxBox(const Collider* collider, const Transform* transform, const Collider* otherCollider, const Transform* otherTransform)
{
    std::cout << "Collision detected Box Box" << std::endl;
    return {};
}

CollisionPoint CollisionDispatcher::Dispatch(const Collider* collider, const Transform* transform, const Collider* otherCollider, const Transform* otherTransform)
{
    auto typeColliderA = static_cast<int>(collider->GetType());
    auto typeColliderB = static_cast<int>(otherCollider->GetType());

    if (typeColliderA > typeColliderB)
    {
        std::swap(collider, otherCollider);
        std::swap(transform, otherTransform);
    }

    CollisionDispatchFunction collisionDispatchFunction = CollisionDispatcher::collisionDispatcher[typeColliderA][typeColliderB];
    if (collisionDispatchFunction)
    {
        std::cout << "Found resolving function: " << typeColliderA << " " << typeColliderB << std::endl;
        return collisionDispatchFunction(collider, transform, otherCollider, otherTransform);
    }
    std::cout << "Did not find function: " << typeColliderA << " " << typeColliderB << std::endl;
    return CollisionPoint();
}

// defining dispatch matrix
CollisionDispatchFunction CollisionDispatcher::collisionDispatcher[static_cast<int>(Collider::ColliderType::COUNT)][static_cast<int>(Collider::ColliderType::COUNT)] = {
    {CollisionDispatcher::IntersectBoxBox, CollisionDispatcher::IntersectBoxSphere},
    {CollisionDispatcher::IntersectBoxSphere, CollisionDispatcher::IntersectSphereSphere}
};



