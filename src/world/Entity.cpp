#include "Entity.h"

Entity::Entity() {
    _uid = Entity::AvailableUid;
    Entity::AvailableUid++;
}

