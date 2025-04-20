#include "Entity.h"

Entity::Entity() {
    _uid = Entity::AvailableUid;
    Entity::AvailableUid++;
    _name = "Cometa" + _uid;
}

Entity::Entity(const std::string& name) {
    _uid = Entity::AvailableUid;
    Entity::AvailableUid++;
    _name = name;
}

Entity::~Entity()
{

}

uint32_t Entity::AvailableUid = 1;