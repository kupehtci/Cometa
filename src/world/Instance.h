#ifndef COMETA_INSTANCE_H
#define COMETA_INSTANCE_H

#include <stdint.h>

class Instance {

private:
    uint32_t _uid;
    static uint32_t AvailableUid;
public:
    Instance();



    // --------- GETTERS AND SETTERS ---------
    uint32_t GetUID() { return _uid;}
};

uint32_t Instance::AvailableUid = 1;


#endif //COMETA_INSTANCE_H
