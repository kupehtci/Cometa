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
        if (!rb._enabled) continue;


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

        // CollisionPoint point = CollisionDispatcher::Dispatch(colliderComp->GetCollider(), rbTransform, colliderComp->GetCollider(),  rbTransform);
        // std::cout << "Collision point: " << point.length << " has collided: " << point.collided << std::endl;
    }

    // TEST COLLISION DISPATCHER


    // BROAD PHASE
    // Calculate collisions
    ComponentStorage<ColliderComponent>& colliders = currentWorld->GetComponentRegistry().GetStorage<ColliderComponent>();

    for (auto colA : colliders)
    {
        for (auto colB : colliders)
        {
            if (colA == colB) continue;
            if (colA.GetCollider() == nullptr || colB.GetCollider() == nullptr) continue;

            Transform* transformA = colA.GetOwner()->GetComponent<Transform>();
            Transform* transformB = colB.GetOwner()->GetComponent<Transform>();

            CollisionPoint point = CollisionDispatcher::Dispatch(colA.GetCollider(), transformA, colB.GetCollider(), transformB);
            std::cout << "Collision check between: " << colA.GetOwner()->GetUID() << " and " << colB.GetOwner()->GetUID() << std::endl;
            std::cout << "point of collision: " << point.collided << std::endl;

            if (point.collided)
            {
                RigidBody* rb = colA.GetOwner()->GetComponent<RigidBody>();
                if (rb != nullptr)
                {
                    rb->_enabled = false;
                }


            }
            else
            {
                RigidBody* rb = colA.GetOwner()->GetComponent<RigidBody>();
                if (rb != nullptr)
                {
                    rb->_enabled = true;
                }
            }

            glm::vec3 center = transformA->position;
            float radius = dynamic_cast<SphereCollider*>(colA.GetCollider())->GetRadius();
            int segments = 24;

            glBegin(GL_LINE_LOOP);
            for (int i = 0; i < segments; ++i) {
                float theta = float(i) / float(segments) * 2.0f * glm::pi<float>();
                glVertex3f(center.x + radius * cos(theta), center.y, center.z + radius * sin(theta));
            }
            glEnd();

            glBegin(GL_LINE_LOOP);
            for (int i = 0; i < segments; ++i) {
                float theta = float(i) / float(segments) * 2.0f * glm::pi<float>();
                glVertex3f(center.x + radius * cos(theta), center.y + radius * sin(theta), center.z);
            }
            glEnd();

            glBegin(GL_LINE_LOOP);
            for (int i = 0; i < segments; ++i) {
                float theta = float(i) / float(segments) * 2.0f * glm::pi<float>();
                glVertex3f(center.x, center.y + radius * cos(theta), center.z + radius * sin(theta));
            }
            glEnd();
        }
    }

    std::cout << "PHYSICS MANAGER: ended step phase" << std::endl;
}

void PhysicsManager::Close(){
    // std::cout << "PhysicsManager::Close()" << std::endl;
}
