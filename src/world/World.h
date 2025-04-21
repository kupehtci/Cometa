#ifndef COMETA_WORLD_H
#define COMETA_WORLD_H

#include "types/SparseSet.h"
#include "world/ComponentRegistry.h"

class Entity;


class World {
    friend class Entity;

  private:
    SparseSet<Entity> _entitiesSparseSet;
    ComponentRegistry _componentRegistry;

public:
    static int worldInstanceCount;
    World();
    ~World();

    // ------------ ENTITIES METHODS ------------
    Entity* CreateEntity(const std::string& name);
    bool DeleteEntity(Entity* entity);


    // // ------------ COMPONENT METHODS ------------
    // // This methods serve as a wrapper between Entity and ComponentRegistry
    //
    // template<typename T>
    // T* CreateComponent(Entity* ent)
    // {
    //     return _componentRegistry->CreateComponent<T>(ent);
    // }
    //
    // template<typename T>
    // void DeleteComponent(Entity* ent)
    // {
    //     _componentRegistry->RemoveComponent<T>(ent);
    // }

};

#endif //COMETA_WORLD_H
