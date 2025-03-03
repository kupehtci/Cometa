#ifndef COMETA_COMPONENT_STORAGE_H
#define COMETA_COMPONENT_STORAGE_H

#include <vector>
// #include <unordered_map>

#include "Entity.h"

// Component storage is an Sparse Set that stores the object more efficiently than ordered maps <id, Entity>
template<typename T>
class ComponentStorage {

private: 
	std::vector<T> _components;
	std::vector<uint32_t> _uid; 
public: 
	ComponentStorage();
};

#endif