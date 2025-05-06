//
// Created by Daniel Laplana Gimeno on 6/5/25.
//
#include "PhysicsManager.h"

#include "world/WorldManager.h"
#include "world/ComponentStorage.h"
#include "world/Components.h"
#include "world/Entity.h"

#include "physics/Collider.h"

// Collision contact points calculation



// end of collision contact points calculation




void PhysicsManager::Init(){
    // std::cout << "PhysicsManager::Init()" << std::endl;
}

void PhysicsManager::Update(){
    // std::cout << "PhysicsManager::Update()" << std::endl;

    float dt = Time::GetDeltaTime();

    WorldManager* worldManager = WorldManagerRef;
    std::shared_ptr<World> currentWorld = worldManager->GetCurrentWorld();

    if (currentWorld == nullptr)
    {
        COMETA_WARNING("[PHYSICS_MANAGER] Current world is not set, cannot calculate physics interactions");
        return;
    }

    ComponentStorage<RigidBody>& rigidBodies = currentWorld->GetComponentRegistry().GetStorage<RigidBody>();

    std::cout << "PHYSICS MANAGER: initialized step phase" << std::endl;
    // STEP PHASE
    // Calculate movements
    for (auto& rb : rigidBodies)
    {
        std::cout << "   Processing rigidbody of owner: " << rb.GetOwner()->GetUID() << std::endl;
        // if (!rb._enabled) continue;


        ColliderComponent* colliderComp = rb.GetOwner()->GetComponent<ColliderComponent>();

        if (colliderComp == nullptr){
            COMETA_MSG("[PHYSICS_MANAGER] Rigidbody owner with UID ", rb.GetOwner()->GetUID() , " has no collider");
            continue;
        }

        Transform* rbTransform = rb.GetOwner()->GetComponent<Transform>();

        // Step phase
        rb._force += rb._mass * _gravity;
        rb._linearVelocity += rb._force / rb._mass * dt;
        rbTransform->position += rb._linearVelocity * dt;

        rb._force = glm::vec3(0.0f, 0.0f, 0.0f);

        CollisionPoint point = CollisionDispatcher::Dispatch(colliderComp->GetCollider(), rbTransform, colliderComp->GetCollider(),  rbTransform);


    }

    // TEST COLLISION DISPATCHER


    // BROAD PHASE
    // Calculate collisions
    // for (auto& rb : rigidBodies)
    // {
    //
    // }

    std::cout << "PHYSICS MANAGER: ended step phase" << std::endl;
}

void PhysicsManager::Close(){
    // std::cout << "PhysicsManager::Close()" << std::endl;
}
