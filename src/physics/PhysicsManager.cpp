//
// Created by Daniel Laplana Gimeno on 6/5/25.
//
#include "PhysicsManager.h"

#include "world/WorldManager.h"
#include "world/ComponentStorage.h"
#include "world/Components.h"
#include "world/Entity.h"

#include "physics/Collider.h"


#define GLAD_GL_IMPLEMENTATION
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Collision contact points calculation



// end of collision contact points calculation




void PhysicsManager::Init(){
    // std::cout << "PhysicsManager::Init()" << std::endl;
}

void PhysicsManager::Update(){
    // // std::cout << "PhysicsManager::Update()" << std::endl;
    //
    // float dt = Time::GetDeltaTime();
    //
    // WorldManager* worldManager = WorldManagerRef;
    // std::shared_ptr<World> currentWorld = worldManager->GetCurrentWorld();
    //
    // if (currentWorld == nullptr)
    // {
    //     COMETA_WARNING("[PHYSICS_MANAGER] Current world is not set, cannot calculate physics interactions");
    //     return;
    // }
    //
    // ComponentStorage<RigidBody>& rigidBodies = currentWorld->GetComponentRegistry().GetStorage<RigidBody>();
    //
    // std::cout << "PHYSICS MANAGER: initialized step phase" << std::endl;
    // // STEP PHASE
    // // Calculate movements
    // for (auto& rb : rigidBodies)
    // {
    //     std::cout << "   Processing rigidbody of owner: " << rb.GetOwner()->GetUID() << std::endl;
    //     if (!rb._enabled) continue;
    //
    //
    //     ColliderComponent* colliderComp = rb.GetOwner()->GetComponent<ColliderComponent>();
    //
    //     if (colliderComp == nullptr){
    //         COMETA_MSG("[PHYSICS_MANAGER] Rigidbody owner with UID ", rb.GetOwner()->GetUID() , " has no collider");
    //         continue;
    //     }
    //
    //     Transform* rbTransform = rb.GetOwner()->GetComponent<Transform>();
    //
    //     // Step phase
    //     rb._force += rb._mass * _gravity;
    //     rb._linearVelocity += rb._force / rb._mass * dt;
    //     rbTransform->position += rb._linearVelocity * dt;
    //
    //     rb._force = glm::vec3(0.0f, 0.0f, 0.0f);
    //
    //     // CollisionPoint point = CollisionDispatcher::Dispatch(colliderComp->GetCollider(), rbTransform, colliderComp->GetCollider(),  rbTransform);
    //     // std::cout << "Collision point: " << point.length << " has collided: " << point.collided << std::endl;
    // }
    //
    // // TEST COLLISION DISPATCHER
    //
    //
    // // BROAD PHASE
    // // Calculate collisions
    // struct Collision
    // {
    //     ColliderComponent* colliderCompA;
    //     ColliderComponent* colliderCompB;
    //     CollisionPoint point;
    //     Collision(ColliderComponent* colliderA, ColliderComponent* colliderB, CollisionPoint point): colliderCompA(colliderA), colliderCompB(colliderB), point(point){};
    // };
    // std::vector<Collision> collisions;
    // ComponentStorage<ColliderComponent>& colliders = currentWorld->GetComponentRegistry().GetStorage<ColliderComponent>();
    //
    // std::vector<ColliderComponent*> colliderList;
    // for (auto& col : colliders) {
    //     colliderList.push_back(&col);
    // }
    //
    // for (size_t i = 0; i < colliderList.size(); ++i) {
    //     for (size_t j = i + 1; j < colliderList.size(); ++j) {
    //         ColliderComponent* colA = colliderList[i];
    //         ColliderComponent* colB = colliderList[j];
    //
    //         if (colA == colB) continue;
    //         if (colA->GetCollider() == nullptr || colB->GetCollider() == nullptr) continue;
    //
    //         Transform* transformA = colA->GetOwner()->GetComponent<Transform>();
    //         Transform* transformB = colB->GetOwner()->GetComponent<Transform>();
    //
    //         CollisionPoint point = CollisionDispatcher::Dispatch(colA->GetCollider(), transformA, colB->GetCollider(), transformB);
    //         std::cout << "Collision check between: " << colA->GetOwner()->GetUID() << " and " << colB->GetOwner()->GetUID() << std::endl;
    //         std::cout << "point of collision: " << point.collided << std::endl;
    //
    //         if (point.collided)
    //         {
    //             Collision collision = {colA, colB, point};
    //             collisions.emplace_back(colA, colB, point);
    //         }
    //     }
    // }
    //
    // for (auto col : collisions)
    // {
    //     std::cout << "Solving collision" << std::endl;
    //     std::cout << "========================================Addding to normal (" << col.point.normal.x << "," << col.point.normal.y << "," << col.point.normal.z << ")" << std::endl;
    //
    //     RigidBody* rbA = col.colliderCompA->GetOwner()->GetComponent<RigidBody>();
    //     RigidBody* rbB = col.colliderCompB->GetOwner()->GetComponent<RigidBody>();
    //
    //     Transform* transformA = col.colliderCompA->GetOwner()->GetComponent<Transform>();
    //     Transform* transformB = col.colliderCompB->GetOwner()->GetComponent<Transform>();
    //
    //     float totalMass = (rbA ? rbA->_mass : 0.0f) + (rbB ? rbB->_mass : 0.0f);
    //
    //     // If both are static (mass = 0), skip
    //     if (totalMass == 0.0f)
    //         continue;
    //
    //     // Positional correction
    //     float correctionRatio = 0.8f;
    //     float slop = 0.5f;
    //     float penetration = std::max(col.point.length - slop, 0.0f);
    //
    //
    //     glm::vec3 correction = col.point.normal * (penetration / totalMass) * correctionRatio;
    //
    //
    //     if (rbA && rbA->_mass > 0.0f)
    //         transformA->position -= correction * (rbB ? rbB->_mass / totalMass : 1.0f);
    //
    //     if (rbB && rbB->_mass > 0.0f)
    //         transformB->position += correction * (rbA ? rbA->_mass / totalMass : 1.0f);
    //
    //     // reset velocity
    //     // if (rbA) rbA->_linearVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
    //     //
    //     // if (rbB) rbB->_linearVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
    //
    //     std::cout << "-----------------------------------RBA vel: " << rbA->_linearVelocity.x << "," << rbA->_linearVelocity.y << std::endl;
    //     if (rbA && rbA->_mass > 0.0f) {
    //         float velAlongNormal = glm::dot(rbA->_linearVelocity, col.point.normal);
    //         if (velAlongNormal < 0)
    //             rbA->_linearVelocity -= col.point.normal * velAlongNormal;
    //     }
    //
    //     if (rbB && rbB->_mass > 0.0f) {
    //         float velAlongNormal = glm::dot(rbB->_linearVelocity, col.point.normal);
    //         if (velAlongNormal > 0)
    //             rbB->_linearVelocity -= col.point.normal * velAlongNormal;
    //     }
    // }
    //
    // std::cout << "PHYSICS MANAGER: ended step phase" << std::endl;

     float dt = Time::GetDeltaTime();

    WorldManager* worldManager = WorldManagerRef;
    std::shared_ptr<World> currentWorld = worldManager->GetCurrentWorld();

    if (currentWorld == nullptr) {
        COMETA_WARNING("[PHYSICS_MANAGER] Current world is not set, cannot calculate physics interactions");
        return;
    }

    ComponentStorage<RigidBody>& rigidBodies = currentWorld->GetComponentRegistry().GetStorage<RigidBody>();

    // STEP PHASE
    for (auto& rb : rigidBodies) {
        if (!rb._enabled) continue;

        ColliderComponent* colliderComp = rb.GetOwner()->GetComponent<ColliderComponent>();
        if (colliderComp == nullptr) {
            COMETA_MSG("[PHYSICS_MANAGER] Rigidbody owner with UID ", rb.GetOwner()->GetUID() , " has no collider");
            continue;
        }

        Transform* rbTransform = rb.GetOwner()->GetComponent<Transform>();

        // Step phase
        rb._force += rb._mass * _gravity;
        rb._linearVelocity += rb._force / rb._mass * dt;
        rbTransform->position += rb._linearVelocity * dt;

        rb._force = glm::vec3(0.0f);
    }

    // BROAD PHASE with improved collision handling
    struct Collision {
        ColliderComponent* colliderCompA;
        ColliderComponent* colliderCompB;
        CollisionPoint point;
        Collision(ColliderComponent* colliderA, ColliderComponent* colliderB, CollisionPoint point)
            : colliderCompA(colliderA), colliderCompB(colliderB), point(point) {}
    };
    std::vector<Collision> collisions;
    ComponentStorage<ColliderComponent>& colliders = currentWorld->GetComponentRegistry().GetStorage<ColliderComponent>();

    std::vector<ColliderComponent*> colliderList;
    for (auto& col : colliders) {
        colliderList.push_back(&col);
    }

    for (size_t i = 0; i < colliderList.size(); ++i) {
        for (size_t j = i + 1; j < colliderList.size(); ++j) {
            ColliderComponent* colA = colliderList[i];
            ColliderComponent* colB = colliderList[j];

            if (colA == colB) continue;
            if (colA->GetCollider() == nullptr || colB->GetCollider() == nullptr) continue;

            Transform* transformA = colA->GetOwner()->GetComponent<Transform>();
            Transform* transformB = colB->GetOwner()->GetComponent<Transform>();

            CollisionPoint point = CollisionDispatcher::Dispatch(colA->GetCollider(), transformA, colB->GetCollider(), transformB);
            std::cout << "Collision check between: " << colA->GetOwner()->GetUID() << " and " << colB->GetOwner()->GetUID() << std::endl;
            std::cout << "point of collision: " << point.collided << std::endl;

            if (point.collided)
            {
                Collision collision = {colA, colB, point};
                collisions.emplace_back(colA, colB, point);
            }
        }
    }


    // COLLISION RESOLUTION with Baumgarte Stabilization


    const float slop = 0.01f;   // Penetration slop

    for (auto& col : collisions) {
        RigidBody* rbA = col.colliderCompA->GetOwner()->GetComponent<RigidBody>();
        RigidBody* rbB = col.colliderCompB->GetOwner()->GetComponent<RigidBody>();

        Transform* transformA = col.colliderCompA->GetOwner()->GetComponent<Transform>();
        Transform* transformB = col.colliderCompB->GetOwner()->GetComponent<Transform>();

        // Skip if both objects are static
        // Objects are static if Mass is 0
        float totalMass = (rbA ? rbA->_mass : 0.0f) + (rbB ? rbB->_mass : 0.0f);
        if (totalMass <= 0.01f) continue;

        // Calculate relative velocity
        glm::vec3 relativeVel = (rbB ? rbB->_linearVelocity : glm::vec3(0.0f)) -
                               (rbA ? rbA->_linearVelocity : glm::vec3(0.0f));

        // Calculate relative velocity along normal
        float velAlongNormal = glm::dot(relativeVel, col.point.normal);

        // Don't resolve if objects are separating
        if (velAlongNormal > 0.0f) continue;

        float restitution = 0.5f; // Coefficient of restitution

        // Baumgarte stabilization term
        float penetration = std::max(col.point.length - slop, 0.0f);
        float baumgarteTerm = (_beta / dt) * penetration;

        // Calculate impulse scalar
        float j = -(1.0f + restitution) * velAlongNormal;
        j += baumgarteTerm; // Add Baumgarte term
        j /= totalMass;

        // Apply impulse
        glm::vec3 impulse = j * col.point.normal;

        if (rbA && rbA->_mass > 0.0f) {
            float massRatioA = rbA->_mass / totalMass;
            rbA->_linearVelocity -= impulse * massRatioA;

            // Position correction with Baumgarte
            transformA->position -= col.point.normal * penetration * _beta * massRatioA;
        }

        if (rbB && rbB->_mass > 0.0f) {
            float massRatioB = rbB->_mass / totalMass;
            rbB->_linearVelocity += impulse * massRatioB;

            // Position correction with Baumgarte
            transformB->position += col.point.normal * penetration * _beta * massRatioB;
        }

        // Apply friction
        const float frictionCoeff = 0.3f;

        // Calculate tangent vector
        glm::vec3 tangent = relativeVel - (col.point.normal * velAlongNormal);
        float tangentLength = glm::length(tangent);

        if (tangentLength > 0.0001f) {
            tangent = glm::normalize(tangent);
            float jt = -glm::dot(relativeVel, tangent);
            jt /= totalMass;

            // Coulomb's law
            float maxFriction = j * frictionCoeff;
            jt = glm::clamp(jt, -maxFriction, maxFriction);

            // Apply friction impulse
            glm::vec3 frictionImpulse = jt * tangent;

            if (rbA && rbA->_mass > 0.0f) {
                rbA->_linearVelocity -= frictionImpulse * (rbA->_mass / totalMass);
            }

            if (rbB && rbB->_mass > 0.0f) {
                rbB->_linearVelocity += frictionImpulse * (rbB->_mass / totalMass);
            }
        }
    }
}

void PhysicsManager::Close(){
    // std::cout << "PhysicsManager::Close()" << std::endl;
}
