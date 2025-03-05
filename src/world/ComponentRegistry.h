#ifndef COMETA_COMPONENT_REGISTRY_H
#define COMETA_COMPONENT_REGISTRY_H

#include "Instance.h"
#include "ComponentStorage.h"

class ComponentRegistry {

private: 

public: 
	ComponentRegistry(); 

	template<typename T>
	void AddComponent(Entity ent, const T& component) {
		GetStorage<T>().Add(ent.GetUID(), component); 
	}

	template<typename T>
	void RemoveComponent(Entity ent) {
		GetStorage<T>().Pop(ent.GetUID()); 
	}

	/**
	* Retrieve the storage for an specific type of component
	*/
	template<typename T>
	ComponentStorage<T>& GetStorage() {
		static ComponentStorage<T> storage; 
		return storage; 
	}
};

#endif // COMETA_COMPONENT_REGISTRY_H