#ifndef COMETA_ENTITY_H
#define COMETA_ENTITY_H

#include <ostream>
#include <string>

#include "world/World.h"

class Entity {

private:
    uint32_t _uid = 0;
    static uint32_t AvailableUid;

    std::string _name = "Default";

    World* _parentWorld = nullptr;

public:
    Entity();
    ~Entity();
    explicit Entity(const std::string& name);

    // ------------ COMPONENTS MANAGEMENT ------------
    template<typename T>
    void CreateComponent()
    {
        std::cout << "Creating component of type: " << typeid(T).name() << std::endl;
    }

    template<typename T>
    T* GetComponent()
    {
        std::cout << "Getting component of type: " << typeid(T).name() << std::endl;
        return nullptr;
    }

    template<typename T>
    void RemoveComponent()
    {
        std::cout << "Removing component of type: " << typeid(T).name() << std::endl;
    }


    template<typename T>
    bool HasComponent()
    {
        std::cout << "Entity::HasComponent()" << typeid(T).name() << std::endl;
        return false;
    }


public:
    // ------------ OPERATOR OVERLOAD ------------
    friend std::ostream& operator<<(std::ostream& os, const Entity& entity)
    {
        os << "Entity UID: " << entity._uid << std::endl;
        return os;
    }

    bool operator==(const Entity& other) const {
        return _uid == other._uid;
    }

    bool operator!=(const Entity& other) const {
        return _uid != other._uid;
    }

public:
    // --------- GETTERS AND SETTERS ---------
    [[nodiscard]] uint32_t GetUID() const { return _uid;}
    [[nodiscard]] std::string GetName() const { return _name;}
    // [[nodiscard]] World* GetParentWorld() const { return _parentWorld;}

    void SetName(const std::string& name) { _name = name;}

    friend class World;
};

#endif //COMETA_ENTITY_H
