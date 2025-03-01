#include "Instance.h"

Instance::Instance() {
    _uid = Instance::AvailableUid;
    Instance::AvailableUid++;
}

