#ifndef COMETA_SCRIPTMANAGER_H
#define COMETA_SCRIPTMANAGER_H

#include <vector>
#include <unordered_map>
#include "world/Components.h"
#include "world/WorldManager.h"
#include "world/World.h"
#include "world/Entity.h"

/**
 * Manager responsible for handling script update and execution
 */
class ScriptManager : public SingletonManager<ScriptManager>{
private:
    // Store active collisions for making enter and exit collision callbacks
    std::unordered_map<uint64_t, bool> _activeCollisions;
    

public:
    ScriptManager() = default;
    ScriptManager(const ScriptManager&) = delete;
    ScriptManager& operator=(const ScriptManager&) = delete;

    /**
     * Generates an unique collision key to represent a collision
     * @param entityA Entity A of the collision
     * @param entityB Entity B of the collision
     * @return unique identifier of the collision
     */
    uint64_t GenerateCollisionKey(Entity* entityA, Entity* entityB) {
        uint32_t idA = entityA->GetUID();
        uint32_t idB = entityB->GetUID();

        if (idA > idB) std::swap(idA, idB);
        return (static_cast<uint64_t>(idA) << 32) | static_cast<uint64_t>(idB);
    }


    void Init() override {}
    void Update() override{
        UpdateScripts(WorldManager::GetInstancePtr()->GetCurrentWorld().get(), Time::GetDeltaTime());
    }
    void Close() override {}

    void InitScripts(World* world) {
        if (!world) return;
        
        auto& scriptStorage = world->GetComponentRegistry().GetStorage<Script>();
        for (auto& script : scriptStorage) {
            script.Init();
        }
    }
    
    // Update all Script components in the world
    void UpdateScripts(World* world, float deltaTime) {
        if (!world) return;
        
        auto& scriptStorage = world->GetComponentRegistry().GetStorage<Script>();
        for (auto& script : scriptStorage) {
            script.Update(deltaTime);
        }
    }
    
    // Process collision events between entities
    void ProcessCollision(Entity* entityA, Entity* entityB, bool isColliding) {
        if (!entityA || !entityB) return;
        
        uint64_t collisionKey = GenerateCollisionKey(entityA, entityB);
        bool wasColliding = _activeCollisions.find(collisionKey) != _activeCollisions.end() && 
                           _activeCollisions[collisionKey];
        
        // Collision started
        if (isColliding && !wasColliding) {
            Script* scriptA = entityA->GetComponent<Script>();
            Script* scriptB = entityB->GetComponent<Script>();
            
            if (scriptA) scriptA->OnCollisionEnter(entityB);
            if (scriptB) scriptB->OnCollisionEnter(entityA);
            
            _activeCollisions[collisionKey] = true;
        }
        // Collision ended
        else if (!isColliding && wasColliding) {
            Script* scriptA = entityA->GetComponent<Script>();
            Script* scriptB = entityB->GetComponent<Script>();
            
            if (scriptA) scriptA->OnCollisionExit(entityB);
            if (scriptB) scriptB->OnCollisionExit(entityA);
            
            _activeCollisions[collisionKey] = false;
        }
    }

};

// Initialize static instance

#define ScriptManagerRef ScriptManager::GetInstancePtr()

#endif // COMETA_SCRIPTMANAGER_H