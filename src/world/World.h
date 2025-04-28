#ifndef COMETA_WORLD_H
#define COMETA_WORLD_H

#include "types/SparseSet.h"
#include "world/ComponentRegistry.h"

class Entity;
class WorldManager;
class Renderer;

class World {
    friend class Entity;
    friend class WorldManager;
    friend class Renderer;

  private:
    SparseSet<Entity> _entities;
    ComponentRegistry _componentRegistry;
    int _uid = -1;

public:
    static int worldInstanceCount;
    World();
    ~World();

    // ------------ ENTITIES METHODS ------------
    Entity* CreateEntity(const std::string& name);
    bool RemoveEntity(const uint32_t& uid);


    // ------------ DEBUG METHODS ------------
    /**
     * Print in console some debug information that indicated the entities stored in World
     * and its components information
     */
    void DebugPrint();

    // ------------ GETTERS AND SETTERS ------------
    [[nodiscard]] size_t GetNumEntities() const {return _entities.Size();}
    [[nodiscard]] ComponentRegistry& GetComponentRegistry() {return _componentRegistry;}

};

#endif //COMETA_WORLD_H
