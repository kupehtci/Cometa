#ifndef COMETA_COMPONENT_REGISTRY_H
#define COMETA_COMPONENT_REGISTRY_H

#include "world/Entity.h"
#include "world/ComponentStorage.h"
#include "world/Components.h"


class ComponentRegistry {

private: 
	std::tuple<
		ComponentStorage<Transform>,
		ComponentStorage<Renderable>,
		ComponentStorage<SpriteRenderable>,
		ComponentStorage<Collider>,
		ComponentStorage<RigidBody>,
		ComponentStorage<Tag>
		> _components;

public: 
	ComponentRegistry() = default;

	/**
	 * Add a pointer to a component as the new component for that entity
	 *
	 * @tparam T
	 * @param ent
	 * @param component
	 */
	template<typename T>
	void AddComponent(Entity* ent, const T* component) {
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
	T* CreateComponent(Entity* ent){
		return GetStorage<T>().Create(ent->GetUID());
	}

	/**
	 * Remove the component from the entity
	 * @tparam T Component to delete
	 * @param ent Entity pointer to delete the component from
	 */
	template<typename T>
	void RemoveComponent(Entity* ent) {
		GetStorage<T>().Pop(ent->GetUID());
	}

	/**
	 * Get a pointer to the specified component that belongs to that Entity
	 * @tparam T Component to get
	 * @param ent Entity who belongs the component to
	 * @return Pointer to the component stored in the ComponentStorage
	 */
	template<typename T>
	T* GetComponent(Entity* ent) {
		// Get returns a pointer to the element stored in the Sparse Set
		return GetStorage<T>().Get(ent->GetUID());
	}

	/**
	* Retrieve the storage for an specific type of component
	*/
	template<typename T>
	ComponentStorage<T>& GetStorage() {
		return std::get<ComponentStorage<T>>(_components);
	}
};

#endif // COMETA_COMPONENT_REGISTRY_H