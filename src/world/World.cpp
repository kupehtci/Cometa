//
// Created by Daniel Laplana Gimeno on 19/4/25.
//

#include "World.h"

#include "world/Components.h"
#include "world/ComponentRegistry.h"

int World::worldInstanceCount = 0;

World::World()
{
    worldInstanceCount++;
    std::cout << "World::World() --> worldInstanceCount: " << worldInstanceCount << std::endl;
    _entitiesSparseSet = SparseSet<Entity>();
    // _componentRegistry= ComponentRegistry();
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
    _entitiesSparseSet.Add(newEntity.GetUID(), newEntity);

    Transform* transform = _componentRegistry.CreateComponent<Transform>(&newEntity);

    std::cout << "new entity created: " << newEntity.GetUID() << " with transform: x: " << transform->translation.x << std::endl;
    transform->translation.x = 1;

    Transform* otherTransformRef = _componentRegistry.GetComponent<Transform>(&newEntity);
    std::cout << "Other entity ref: " << newEntity.GetUID() << " with transform: x: " << otherTransformRef->translation.x << std::endl;

    return _entitiesSparseSet.Get(newUid);
}

/**
 * Delete an entity and its components associated
 * @param entity Entity* to delete
 * @return bool that indicated the success in deleting the Entity. It will return false if Entity is not contained in this World or cannot delete.
 */
bool DeleteEntity(Entity* entity)
{
    // TODO: Remain to implement delete an entity
    return false;
}