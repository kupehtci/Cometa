#include "Entity.h"

Entity::Entity() {
    _uid = Entity::AvailableUid;
    Entity::AvailableUid++;
}

uint32_t Entity::AvailableUid = 1;