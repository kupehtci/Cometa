#include "World.h"

#include <iostream>

#include "world/Entity.h"
// #include "world/Components.h"
// #include "world/ComponentRegistry.h"

int World::worldInstanceCount = 0;

World::World()
{
    worldInstanceCount++;
    std::cout << "World::World() --> worldInstanceCount: " << worldInstanceCount << std::endl;
    _entitiesSparseSet = SparseSet<Entity>();
    // _componentRegistry = ComponentRegistry();
}
World::~World()
{

}

/**
 * Create an entity and store in the world.
 * The entity is created together with a Transform
 * @param name name of the entity
 * @return Entity* pointer to the entity
 */
Entity* World::CreateEntity(const std::string& name)
{
    Entity newEntity = Entity(name);
    uint32_t newUid = newEntity.GetUID();
    newEntity._parentWorld = this;
    _entitiesSparseSet.Add(newUid, newEntity);
    std::cout << "previous to create component transform " << std::endl;

    Transform* transform = newEntity.CreateComponent<Transform>();

    std::cout << "Created entity with transform : " << transform->translation.x << std::endl;
    transform->translation.x = 1;
    transform = newEntity.GetComponent<Transform>();
    std::cout << "Created entity with transform : " << transform->translation.x << std::endl;

    return _entitiesSparseSet.Get(newUid);
}


/**
 * Delete an entity and its components associated
 * @param entity Entity* to delete
 * @return bool that indicated the success in deleting the Entity. It will return false if Entity is not contained in this World or cannot delete.
 */
bool World::DeleteEntity(Entity* entity)
{
    return false;
}

// --------------- ENTITIES METHODS IMPLEMENTATIONS ---------------


// --------------- END OF ENTITIES METHODS IMPLEMENTATIONS ---------------
