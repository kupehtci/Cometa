//
// Created by Daniel Laplana Gimeno on 6/5/25.
//

#include "CollisionDispatcher.h"

#include <complex>

#include "physics/Collider.h"
#include "physics/Collider.h"
#include "world/Components.h"

#include <iostream>

// Enable this if want to debug collisions using the console
// #define PHYSICS_DEBUG

glm::mat3 EulerAnglesXYZ(const glm::vec3& angles) {
    glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), angles.x, glm::vec3(1, 0, 0));
    glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), angles.y, glm::vec3(0, 1, 0));
    glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), angles.z, glm::vec3(0, 0, 1));
    return glm::mat3(rotZ * rotY * rotX); // XYZ order
}

// Need to swap the lower ColliderType to the first argument and higher ColliderType to the second argument
CollisionPoint CollisionDispatcher::IntersectBoxSphere(const Collider* collider, const Transform* transform, const Collider* otherCollider, const Transform* otherTransform)
{
#ifdef PHYSICS_DEBUG
    std::cout << "Collision detected Box sphere" << std::endl;
#endif
//
//     CollisionPoint result{};
//
//     // Cast colliders to their specific types
//     const auto* box = dynamic_cast<const BoxCollider*>(collider);
//     const auto* sphere = dynamic_cast<const SphereCollider*>(otherCollider);
//
//     // Get sphere center in world space
//     glm::vec3 sphereCenter = otherTransform->position + sphere->GetCenter();
//     float sphereRadius = sphere->GetRadius();
//
//     // Get box transform
//     glm::vec3 boxCenter = transform->position + box->GetCenter();
//     glm::vec3 boxHalfSize = box->GetExtents();
//
//     // Get box rotation matrix
//     glm::mat3 boxRotation = glm::mat3(EulerAnglesXYZ(
//         {glm::radians(transform->rotation.x),
//          glm::radians(transform->rotation.y),
//          glm::radians(transform->rotation.z)}
//     ));
//
//     // Transform sphere center to box local space
//     glm::vec3 localSphereCenter = glm::transpose(boxRotation) * (sphereCenter - boxCenter);
//
//     // Find closest point on box to sphere center in local space
//     glm::vec3 closestPoint;
//     closestPoint.x = glm::clamp(localSphereCenter.x, -boxHalfSize.x, boxHalfSize.x);
//     closestPoint.y = glm::clamp(localSphereCenter.y, -boxHalfSize.y, boxHalfSize.y);
//     closestPoint.z = glm::clamp(localSphereCenter.z, -boxHalfSize.z, boxHalfSize.z);
//
//     // Transform closest point back to world space
//     glm::vec3 worldClosestPoint = boxRotation * closestPoint + boxCenter;
//
//     // Calculate distance and normal
//     glm::vec3 delta = sphereCenter - worldClosestPoint;
//     float distance = glm::length(delta);
//
//     // Check for collision
//     if (distance <= sphereRadius) {
//         result.collided = true;
//
//         // Calculate normal - pointing from box to sphere
//         if (distance > 0.0001f) {
//             result.normal = glm::normalize(delta);
//         } else {
//             // If the sphere center is exactly at the closest point, use a default normal
//             // Find which face of the box we're closest to in local space
//             glm::vec3 absLocalSphereCenter = glm::abs(localSphereCenter);
//             if (absLocalSphereCenter.x >= absLocalSphereCenter.y && absLocalSphereCenter.x >= absLocalSphereCenter.z) {
//                 result.normal = boxRotation * glm::vec3(glm::sign(localSphereCenter.x), 0.0f, 0.0f);
//             } else if (absLocalSphereCenter.y >= absLocalSphereCenter.x && absLocalSphereCenter.y >= absLocalSphereCenter.z) {
//                 result.normal = boxRotation * glm::vec3(0.0f, glm::sign(localSphereCenter.y), 0.0f);
//             } else {
//                 result.normal = boxRotation * glm::vec3(0.0f, 0.0f, glm::sign(localSphereCenter.z));
//             }
//         }
//
//         // Calculate penetration depth
//         result.length = sphereRadius - distance;
//         result.point = worldClosestPoint; // Contact point on the box
//
//         // Calculate contact points
//         result.a = worldClosestPoint; // Point on the box
//         result.b = sphereCenter - result.normal * sphereRadius; // Point on the sphere
//
// #ifdef PHYSICS_DEBUG
//         std::cout << "Box-Sphere collision: depth=" << result.length
//                   << ", normal=(" << result.normal.x << "," << result.normal.y << "," << result.normal.z << ")"
//                   << ", box pos=(" << boxCenter.x << "," << boxCenter.y << "," << boxCenter.z << ")"
//                   << ", sphere pos=(" << sphereCenter.x << "," << sphereCenter.y << "," << sphereCenter.z << ")" << std::endl;
// #endif
//     }
//
//     return result;

    CollisionPoint result{};

    const auto* box = dynamic_cast<const BoxCollider*>(collider);
    const auto* sphere = dynamic_cast<const SphereCollider*>(otherCollider);

    glm::vec3 sphereCenter = otherTransform->position;
    float sphereRadius = sphere->GetRadius();

    glm::vec3 boxCenter = transform->position + box->GetCenter();
    glm::vec3 boxHalfSize = box->GetExtents();

    glm::mat3 boxRotation = glm::mat3(EulerAnglesXYZ(
        {glm::radians(transform->rotation.x),
         glm::radians(transform->rotation.y),
         glm::radians(transform->rotation.z)}
    ));

    glm::vec3 localSphereCenter = glm::transpose(boxRotation) * (sphereCenter - boxCenter);

    glm::vec3 closestPoint;
    closestPoint.x = glm::clamp(localSphereCenter.x, -boxHalfSize.x, boxHalfSize.x);
    closestPoint.y = glm::clamp(localSphereCenter.y, -boxHalfSize.y, boxHalfSize.y);
    closestPoint.z = glm::clamp(localSphereCenter.z, -boxHalfSize.z, boxHalfSize.z);

    glm::vec3 worldClosestPoint = boxRotation * closestPoint + boxCenter;

    glm::vec3 delta = sphereCenter - worldClosestPoint;
    float distance = glm::length(delta);

    if (distance <= sphereRadius) {
        result.collided = true;
        result.point = worldClosestPoint;
        result.normal = glm::normalize(delta);
        result.length = sphereRadius - distance;

        result.a = worldClosestPoint;
        result.b = sphereCenter - result.normal * sphereRadius;
    }

    return result;
}

CollisionPoint CollisionDispatcher::IntersectSphereSphere(const Collider* collider, const Transform* transform, const Collider* otherCollider, const Transform* otherTransform)
{
#ifdef PHYSICS_DEBUG
    std::cout << "Collision detected sphere sphere" << std::endl;
#endif

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
#ifdef PHYSICS_DEBUG
    std::cout << "Collision detected Box Box" << std::endl;
#endif

     CollisionPoint point;

    const auto* box1 = dynamic_cast<const BoxCollider*>(collider);
    const auto* box2 = dynamic_cast<const BoxCollider*>(otherCollider);

    // Get box centers and extents
    glm::vec3 center1 = transform->position + box1->GetCenter();
    glm::vec3 center2 = otherTransform->position + box2->GetCenter();
    glm::vec3 extents1 = box1->GetExtents();
    glm::vec3 extents2 = box2->GetExtents();

    // Get rotation matrices
    glm::mat3 rotation1 = glm::mat3(EulerAnglesXYZ(
        {glm::radians(transform->rotation.x),
        glm::radians(transform->rotation.y),
        glm::radians(transform->rotation.z)}
    ));

    glm::mat3 rotation2 = glm::mat3(EulerAnglesXYZ(
        {glm::radians(otherTransform->rotation.x),
        glm::radians(otherTransform->rotation.y),
        glm::radians(otherTransform->rotation.z)}
    ));

    // Simple distance check first
    float maxDistance = glm::length(extents1) + glm::length(extents2);
    if (glm::distance(center1, center2) > maxDistance) {
        point.collided = false;
        return point;
    }

    // Transform box2 into box1's local space
    glm::vec3 d = center2 - center1;
    glm::mat3 rotationToLocal = glm::transpose(rotation1);
    glm::vec3 localD = rotationToLocal * d;

    // Get axes for SAT test
    std::vector<glm::vec3> axes;
    // Box1 axes
    axes.push_back(rotation1[0]);
    axes.push_back(rotation1[1]);
    axes.push_back(rotation1[2]);
    // Box2 axes
    axes.push_back(rotation2[0]);
    axes.push_back(rotation2[1]);
    axes.push_back(rotation2[2]);

    float minOverlap = FLT_MAX;
    glm::vec3 collisionNormal;

    // Check overlap along each axis
    for (const auto& axis : axes) {
        // Project centers and extents onto axis
        float c1 = glm::dot(center1, axis);
        float c2 = glm::dot(center2, axis);

        // Project extents
        float e1 = glm::abs(glm::dot(extents1 * rotation1[0], axis)) +
                   glm::abs(glm::dot(extents1 * rotation1[1], axis)) +
                   glm::abs(glm::dot(extents1 * rotation1[2], axis));

        float e2 = glm::abs(glm::dot(extents2 * rotation2[0], axis)) +
                   glm::abs(glm::dot(extents2 * rotation2[1], axis)) +
                   glm::abs(glm::dot(extents2 * rotation2[2], axis));

        float overlap = e1 + e2 - glm::abs(c2 - c1);

        if (overlap <= 0) {
            point.collided = false;
            return point;
        }

        if (overlap < minOverlap) {
            minOverlap = overlap;
            collisionNormal = axis * (c2 - c1 < 0 ? -1.0f : 1.0f);
        }
    }

    point.collided = true;
    point.normal = glm::normalize(collisionNormal);
    point.length = minOverlap;

    // Calculate contact points
    point.a = center1 + point.normal * (point.length * 0.5f);
    point.b = center2 - point.normal * (point.length * 0.5f);
    point.point = (point.a + point.b) * 0.5f;

    return point;
}


CollisionPoint CollisionDispatcher::Dispatch(const Collider* collider, const Transform* transform, const Collider* otherCollider, const Transform* otherTransform)
{
    // Check if any of the pointers are null
    if (!collider || !transform || !otherCollider || !otherTransform) {
        std::cout << "Error: Null pointer passed to Dispatch function" << std::endl;
        return {};
    }
    
    // Check if the collider types are valid
    auto typeColliderA = static_cast<int>(collider->GetType());
    auto typeColliderB = static_cast<int>(otherCollider->GetType());
<<<<<<< HEAD
    
    // Validate collider types are within bounds
    if (typeColliderA < 0 || typeColliderA >= static_cast<int>(Collider::ColliderType::COUNT) ||
        typeColliderB < 0 || typeColliderB >= static_cast<int>(Collider::ColliderType::COUNT)) {
        std::cout << "Error: Invalid collider type in Dispatch" << std::endl;
        return {};
    }

    if (typeColliderA > typeColliderB)
    {
        std::swap(collider, otherCollider);
        std::swap(transform, otherTransform);
    }
=======
    //
    // if (typeColliderA > typeColliderB)
    // {
    //     std::swap(collider, otherCollider);
    //     std::swap(transform, otherTransform);
    //     std::swap(typeColliderA, typeColliderB);
    // }
>>>>>>> develop

    CollisionDispatchFunction collisionDispatchFunction = CollisionDispatcher::collisionDispatcher[typeColliderA][typeColliderB];
    if (collisionDispatchFunction)
    {
#ifdef PHYSICS_DEBUG
        std::cout << "Found resolving function: " << typeColliderA << " " << typeColliderB << std::endl;
#endif
        return collisionDispatchFunction(collider, transform, otherCollider, otherTransform);
    }
    std::cout << "Did not find function: " << typeColliderA << " " << typeColliderB << std::endl;
    return {};
}

// Plane-Box collision detection
CollisionPoint CollisionDispatcher::IntersectPlaneBox(const Collider* collider, const Transform* transform, const Collider* otherCollider, const Transform* otherTransform)
{
    std::cout << "Collision detected Plane-Box" << std::endl;
    CollisionPoint result{};
    
    // Cast colliders to their specific types
    const auto* plane = dynamic_cast<const PlaneCollider*>(collider);
    const auto* box = dynamic_cast<const BoxCollider*>(otherCollider);
    
    // Check if casts were successful
    // if (!plane || !box || !transform || !otherTransform) {
    //     std::cout << "Error: Invalid collider types in IntersectPlaneBox" << std::endl;
    //     return result;
    // }
    if(!plane ){
        std::cout << "Error: Invalid plane in IntersectPlaneBox" << std::endl;
        return result;
    }
    else if(!box){
        std::cout << "Error: Invalid box in IntersectPlaneBox" << std::endl;
        return result;
    }
    else if(!transform){
        std::cout << "Error: Invalid transform in IntersectPlaneBox" << std::endl;
        return result;
    }
    else if(!otherTransform){
        std::cout << "Error: Invalid otherTransform in IntersectPlaneBox" << std::endl;
        return result;
    }
    
    // Get plane properties in world space
    glm::vec3 planeNormal = plane->GetNormal();
    float planeDistance = plane->GetDistance();
    
    // Get box transform
    glm::vec3 boxCenter = otherTransform->position;
    glm::vec3 boxHalfSize = box->GetExtents();
    
    // Get box rotation matrix
    glm::mat3 boxRotation = glm::mat3(EulerAnglesXYZ(
        {glm::radians(otherTransform->rotation.x),
         glm::radians(otherTransform->rotation.y),
         glm::radians(otherTransform->rotation.z)}
    ));
    
    // Calculate box vertices in world space
    glm::vec3 vertices[8];
    vertices[0] = boxCenter + boxRotation * glm::vec3(-boxHalfSize.x, -boxHalfSize.y, -boxHalfSize.z);
    vertices[1] = boxCenter + boxRotation * glm::vec3(boxHalfSize.x, -boxHalfSize.y, -boxHalfSize.z);
    vertices[2] = boxCenter + boxRotation * glm::vec3(-boxHalfSize.x, boxHalfSize.y, -boxHalfSize.z);
    vertices[3] = boxCenter + boxRotation * glm::vec3(boxHalfSize.x, boxHalfSize.y, -boxHalfSize.z);
    vertices[4] = boxCenter + boxRotation * glm::vec3(-boxHalfSize.x, -boxHalfSize.y, boxHalfSize.z);
    vertices[5] = boxCenter + boxRotation * glm::vec3(boxHalfSize.x, -boxHalfSize.y, boxHalfSize.z);
    vertices[6] = boxCenter + boxRotation * glm::vec3(-boxHalfSize.x, boxHalfSize.y, boxHalfSize.z);
    vertices[7] = boxCenter + boxRotation * glm::vec3(boxHalfSize.x, boxHalfSize.y, boxHalfSize.z);
    
    // Find the most negative and most positive distance from the plane
    float minDistance = std::numeric_limits<float>::max();
    float maxDistance = -std::numeric_limits<float>::max();
    int minIndex = -1;
    int maxIndex = -1;
    
    for (int i = 0; i < 8; i++) {
        float distance = glm::dot(planeNormal, vertices[i]) - planeDistance;
        if (distance < minDistance) {
            minDistance = distance;
            minIndex = i;
        }
        if (distance > maxDistance) {
            maxDistance = distance;
            maxIndex = i;
        }
    }
    
    // Check if box intersects plane
    if (minDistance * maxDistance <= 0) { // If signs are different, there's an intersection
        result.collided = true;
        result.normal = planeNormal;
        
        // Calculate penetration depth
        result.length = std::abs(minDistance);
        
        // Set contact point at the vertex with minimum distance
        result.point = vertices[minIndex];
        result.a = result.point + planeNormal * result.length; // Point on plane
        result.b = result.point; // Point on box
    }
    
    return result;
}

// Plane-Sphere collision detection
CollisionPoint CollisionDispatcher::IntersectPlaneSphere(const Collider* collider, const Transform* transform, const Collider* otherCollider, const Transform* otherTransform)
{
    std::cout << "Collision detected Plane-Sphere" << std::endl;
    CollisionPoint result{};
    
    // Cast colliders to their specific types
    const auto* plane = dynamic_cast<const PlaneCollider*>(collider);
    const auto* sphere = dynamic_cast<const SphereCollider*>(otherCollider);
    
    // Check if casts were successful
    if (!plane || !sphere || !transform || !otherTransform) {
        std::cout << "Error: Invalid collider types in IntersectPlaneSphere" << std::endl;
        return result;
    }
    
    // Get plane properties
    glm::vec3 planeNormal = plane->GetNormal();
    float planeDistance = plane->GetDistance();
    
    // Get sphere properties
    glm::vec3 sphereCenter = otherTransform->position;
    float sphereRadius = sphere->GetRadius();
    
    // Calculate signed distance from sphere center to plane
    float signedDistance = glm::dot(planeNormal, sphereCenter) - planeDistance;
    
    // Check for collision
    if (std::abs(signedDistance) <= sphereRadius) {
        result.collided = true;
        result.normal = planeNormal * (signedDistance < 0 ? -1.0f : 1.0f);
        result.length = sphereRadius - std::abs(signedDistance);
        
        // Calculate contact point
        result.point = sphereCenter - planeNormal * signedDistance;
        result.a = result.point; // Point on plane
        result.b = sphereCenter - planeNormal * signedDistance * (signedDistance < 0 ? -1.0f : 1.0f); // Point on sphere
    }
    
    return result;
}

// Plane-Plane collision detection
CollisionPoint CollisionDispatcher::IntersectPlanePlane(const Collider* collider, const Transform* transform, const Collider* otherCollider, const Transform* otherTransform)
{
    std::cout << "Collision detected Plane-Plane" << std::endl;
    CollisionPoint result{};
    
    // Cast colliders to their specific types
    const auto* plane1 = dynamic_cast<const PlaneCollider*>(collider);
    const auto* plane2 = dynamic_cast<const PlaneCollider*>(otherCollider);
    
    // Check if casts were successful
    if (!plane1 || !plane2 || !transform || !otherTransform) {
        std::cout << "Error: Invalid collider types in IntersectPlanePlane" << std::endl;
        return result;
    }
    
    // Get plane properties
    glm::vec3 normal1 = plane1->GetNormal();
    float distance1 = plane1->GetDistance();
    glm::vec3 normal2 = plane2->GetNormal();
    float distance2 = plane2->GetDistance();
    
    // Calculate the direction of the line of intersection
    glm::vec3 lineDir = glm::cross(normal1, normal2);
    float lineLength = glm::length(lineDir);
    
    // Check if planes are parallel (cross product is zero)
    if (lineLength < 0.0001f) {
        // Planes are parallel, check if they are coincident
        if (std::abs(distance1 - distance2) < 0.0001f) {
            // Planes are coincident, consider them as colliding
            result.collided = true;
            result.normal = normal1;
            result.length = 0.0f;
            result.point = glm::vec3(0.0f); // Arbitrary point on the plane
            result.a = result.point;
            result.b = result.point;
        }
        return result;
    }
    
    // Normalize the line direction
    lineDir = lineDir / lineLength;
    
    // Calculate a point on the line of intersection
    // Using the formula from: http://geomalgorithms.com/a05-_intersect-1.html
    float d1 = -distance1; // Adjust for our plane equation format
    float d2 = -distance2;
    
    float det = glm::dot(normal1, normal1) * glm::dot(normal2, normal2) - glm::dot(normal1, normal2) * glm::dot(normal1, normal2);
    if (std::abs(det) < 0.0001f) {
        // Shouldn't happen if we already checked for parallel planes
        return result;
    }
    
    float c1 = (d1 * glm::dot(normal2, normal2) - d2 * glm::dot(normal1, normal2)) / det;
    float c2 = (d2 * glm::dot(normal1, normal1) - d1 * glm::dot(normal1, normal2)) / det;
    
    glm::vec3 pointOnLine = c1 * normal1 + c2 * normal2;
    
    // Planes intersect along a line
    result.collided = true;
    result.normal = glm::normalize(normal1 + normal2); // Average of normals
    result.length = 0.0f; // No penetration depth for intersecting planes
    result.point = pointOnLine;
    result.a = pointOnLine;
    result.b = pointOnLine;
    
    return result;
}

// Dispatch matrix definition
// This dispatch matrix is used for retrieving the correct function for resolving the Collision
CollisionDispatchFunction CollisionDispatcher::collisionDispatcher[static_cast<int>(Collider::ColliderType::COUNT)][static_cast<int>(Collider::ColliderType::COUNT)] = {
    {CollisionDispatcher::IntersectBoxBox, CollisionDispatcher::IntersectBoxSphere, CollisionDispatcher::IntersectPlaneBox},
    {CollisionDispatcher::IntersectBoxSphere, CollisionDispatcher::IntersectSphereSphere, CollisionDispatcher::IntersectPlaneSphere},
    {CollisionDispatcher::IntersectPlaneBox, CollisionDispatcher::IntersectPlaneSphere, CollisionDispatcher::IntersectPlanePlane}
};



