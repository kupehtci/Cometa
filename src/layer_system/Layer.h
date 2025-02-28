#ifndef COMETA_LAYER_H
#define COMETA_LAYER_H

#include "Event.h"

class Layer{

private: 


public:
    // Layer();
    ~Layer();
    
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Close() = 0;

    virtual void HandleEvent(Event& event) = 0;
}; 

#endif
