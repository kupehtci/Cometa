#ifndef COMETA_ONION_H
#define COMETA_ONION_H

#include <vector>

#include "Layer.h"

class Onion {
private: 
    std::vector<Layer*> _layers;

    void Init();
    void Update(); 
    void Close(); 

    void PushLayer(Layer* layer);
    void PopLayer(Layer* layer);

    std::vector<Layer*>::iterator begin() {return _layers.begin();}
    std::vector<Layer*>::iterator end() { return _layers.end(); }
}; 

#endif