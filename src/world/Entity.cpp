#include "Entity.h"

uint32_t Entity::AvailableUid = 1;

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

