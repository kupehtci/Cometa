#ifndef COMETA_ENTITY_H
#define COMETA_ENTITY_H

#include <stdint.h>

class Entity {

private:
    uint32_t _uid;
    static uint32_t AvailableUid;
public:
    Entity();



    // --------- GETTERS AND SETTERS ---------
    uint32_t GetUID() { return _uid;}
};

uint32_t Entity::AvailableUid = 1;


#endif //COMETA_ENTITY_H
