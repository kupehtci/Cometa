//
// Created by Daniel Laplana Gimeno on 6/5/25.
//

#include "CollisionDispatcher.h"

#include <complex>

#include "physics/Collider.h"
#include "physics/Collider.h"
#include "world/Components.h"

#include <iostream>

// Need to swap the lower ColliderType to the first argument and higher ColliderType to the second argument
CollisionPoint CollisionDispatcher::IntersectBoxSphere(const Collider* collider, const Transform* transform, const Collider* otherCollider, const Transform* otherTransform)
{
    std::cout << "Collision detected Box sphere" << std::endl;
    CollisionPoint result{};

    // Cast colliders to their specific types
    const auto* box = dynamic_cast<const BoxCollider*>(collider);
    const auto* sphere = dynamic_cast<const SphereCollider*>(otherCollider);

    // Get sphere center in world space
    glm::vec3 sphereCenter = otherTransform->position;
    float sphereRadius = sphere->GetRadius();

    // Get box in world space
    glm::vec3 boxCenter = transform->position;
    glm::vec3 boxHalfSize = box->GetExtents();

    // Clamp sphere center to box bounds
    glm::vec3 closestPoint;
    closestPoint.x = glm::clamp(sphereCenter.x, boxCenter.x - boxHalfSize.x, boxCenter.x + boxHalfSize.x);
    closestPoint.y = glm::clamp(sphereCenter.y, boxCenter.y - boxHalfSize.y, boxCenter.y + boxHalfSize.y);
    closestPoint.z = glm::clamp(sphereCenter.z, boxCenter.z - boxHalfSize.z, boxCenter.z + boxHalfSize.z);

    // Calculate distance between closest point and sphere center
    float distance = glm::length(sphereCenter - closestPoint);

    // Check if collision occurred
    if (distance <= sphereRadius) {
        result.collided = true;
        result.point = closestPoint;
        result.normal = glm::normalize(sphereCenter - closestPoint);
        result.length = sphereRadius - distance;
    }

    return result;
}

CollisionPoint CollisionDispatcher::IntersectSphereSphere(const Collider* collider, const Transform* transform, const Collider* otherCollider, const Transform* otherTransform)
{
    std::cout << "Collision detected sphere sphere" << std::endl;
    CollisionPoint point{};
    const auto* a = dynamic_cast<const SphereCollider* >(collider);
    const auto* b = dynamic_cast<const SphereCollider* >(otherCollider);

    glm::vec3 centerA = transform->position + a->GetCenter();
    glm::vec3 centerB = otherTransform->position + b->GetCenter();

    glm::vec3 del = centerB - centerA;
    glm::vec3 norm = glm::normalize(del);

    float distance = glm::length(del);
    float radiusSum = a->GetRadius() + b->GetRadius();


    point.a = centerA + (norm * a->GetRadius());
    point.b = centerB - (norm * b->GetRadius());
    point.normal = norm;
    point.length = (radiusSum) - distance;
    point.collided = (distance < radiusSum);

    return point;
}

CollisionPoint CollisionDispatcher::IntersectBoxBox(const Collider* collider, const Transform* transform, const Collider* otherCollider, const Transform* otherTransform)
{
    std::cout << "Collision detected Box Box" << std::endl;
    CollisionPoint point;

    const auto* box1 = dynamic_cast<const BoxCollider*>(collider);
    const auto* box2 = dynamic_cast<const BoxCollider*>(otherCollider);

    glm::vec3 center1 = transform->position;
    glm::vec3 center2 = otherTransform->position;

    glm::vec3 halfSize1 = box1->GetExtents();
    glm::vec3 halfSize2 = box2->GetExtents();

    glm::vec3 delta = center2 - center1;

    // Calculate overlap of the two colliders
    glm::vec3 overlap;
    overlap.x = halfSize1.x + halfSize2.x - std::abs(delta.x);
    overlap.y = halfSize1.y + halfSize2.y - std::abs(delta.y);
    overlap.z = halfSize1.z + halfSize2.z - std::abs(delta.z);

    if (overlap.x <= 0 || overlap.y <= 0 || overlap.z <= 0) {
        point.point = glm::vec3(0, 0, 0);
        point.normal = glm::normalize(center2 - center1);
        point.collided = false;
        return point;
    }

    point.collided = true;

    // Calculate collision normal
    if (overlap.x <= overlap.y && overlap.x <= overlap.z) {
        point.normal = glm::vec3(delta.x < 0 ? -1.0f : 1.0f, 0.0f, 0.0f);
        point.length = overlap.x;
    } else if (overlap.y <= overlap.z) {
        point.normal = glm::vec3(0.0f, delta.y < 0 ? -1.0f : 1.0f, 0.0f);
        point.length = overlap.y;
    } else {
        point.normal = glm::vec3(0.0f, 0.0f, delta.z < 0 ? -1.0f : 1.0f);
        point.length = overlap.z;
    }

    // calculate center of the a and b
    glm::vec3 box1Edge = center1 + point.normal * halfSize1;
    glm::vec3 box2Edge = center2 - point.normal * halfSize2;
    point.a = box1Edge;
    point.b = box2Edge;
    point.point = (box1Edge + box2Edge) * 0.5f;

    return point;
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
    return {};
}

// Dispatch matrix definition
// This dispatch matrix is used fot retrieving the correct function for resolving the Collision
CollisionDispatchFunction CollisionDispatcher::collisionDispatcher[static_cast<int>(Collider::ColliderType::COUNT)][static_cast<int>(Collider::ColliderType::COUNT)] = {
    {CollisionDispatcher::IntersectBoxBox, CollisionDispatcher::IntersectBoxSphere},
    {CollisionDispatcher::IntersectBoxSphere, CollisionDispatcher::IntersectSphereSphere}
};



