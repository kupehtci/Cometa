#ifndef COMETA_COMPONENT_REGISTRY_H
#define COMETA_COMPONENT_REGISTRY_H

#include "world/Entity.h"
#include "world/ComponentStorage.h"
#include "world/Components.h"

class ComponentRegistry {

private: 

public: 
	ComponentRegistry(){}

	/**
	 * Add a pointer to a component as the new component for that entity
	 *
	 * @tparam T
	 * @param ent
	 * @param component
	 */
	template<typename T>
	static void AddComponent(Entity* ent, const T* component) {
		GetStorage<T>().Add(ent->GetUID(), component);

		auto c = static_cast<Component* >(component);
		c->_owner = ent;
	}

	/**
	 * Create the specified T component and assign to the Entity
	 * @tparam T new component to be created for the entity
	 * @param ent Entity to assign the component to.
	 * @return pointer to the new component created
	 */
	template<typename T>
	static T* CreateComponent(Entity* ent){
		return GetStorage<T>().Create(ent->GetUID());
	}

	/**
	 * Remove the component from the entity
	 * @tparam T Component to delete
	 * @param ent Entity pointer to delete the component from
	 */
	template<typename T>
	static void RemoveComponent(Entity* ent) {
		GetStorage<T>().Pop(ent->GetUID());
	}

	/**
	 * Get a pointer to the specified component that belongs to that Entity
	 * @tparam T Component to get
	 * @param ent Entity who belongs the component to
	 * @return Pointer to the component stored in the ComponentStorage
	 */
	template<typename T>
	static T* GetComponent(Entity* ent) {
		return &GetStorage<T>().Get(ent->GetUID());
	}

	// template<typename T>
	// static T* GetComponentPointer(Entity* ent) {
	// 	return &GetStorage<T>().Get(ent->GetUID());
	// }

	/**
	* Retrieve the storage for an specific type of component
	*/
	template<typename T>
	static ComponentStorage<T>& GetStorage() {
		static ComponentStorage<T> storage; 
		return storage; 
	}
};

#endif // COMETA_COMPONENT_REGISTRY_H