//
// Created by Daniel Laplana Gimeno on 19/4/25.
//

#ifndef COMETA_WORLD_H
#define COMETA_WORLD_H

#include "world/Entity.h"
#include "types/SparseSet.h"
#include "ComponentRegistry.h"

#include <vector>


class World {
  private:
    SparseSet<Entity*> _entitiesSparseSet;
    ComponentRegistry _componentRegistry;

public:
    World();
    ~World();

    Entity* CreateEntity(const std::string& name);
    bool DeleteEntity(Entity* entity);
};



#endif //COMETA_WORLD_H
