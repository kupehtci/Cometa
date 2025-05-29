#ifndef COMETA_SCRIPTMANAGER_H
#define COMETA_SCRIPTMANAGER_H

#include <vector>
#include <unordered_map>
#include "world/Components.h"
#include "world/WorldManager.h"
#include "world/World.h"
#include "world/Entity.h"

/**
 * System responsible for managing and updating Script components
 */
class ScriptManager : public SingletonManager<ScriptManager>{
private:
    // Track active collisions to detect enter/exit events
    std::unordered_map<uint64_t, bool> _activeCollisions;
    

public:
    // Private constructor for singleton pattern
    ScriptManager() = default;
    // Delete copy constructor and assignment operator
    ScriptManager(const ScriptManager&) = delete;
    ScriptManager& operator=(const ScriptManager&) = delete;

    // Generate a unique key for a collision pair
    uint64_t GenerateCollisionKey(Entity* entityA, Entity* entityB) {
        uint32_t idA = entityA->GetUID();
        uint32_t idB = entityB->GetUID();
        // Ensure consistent ordering regardless of which entity is A or B
        if (idA > idB) std::swap(idA, idB);
        return (static_cast<uint64_t>(idA) << 32) | static_cast<uint64_t>(idB);
    }

    void Init() override {}
    void Update() override{
        UpdateScripts(WorldManager::GetInstancePtr()->GetCurrentWorld().get(), Time::GetDeltaTime());
    }
    void Close() override {}
    
    // Initialize all Script components in the world
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