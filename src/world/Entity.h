#ifndef COMETA_ENTITY_H
#define COMETA_ENTITY_H

#include <ostream>
#include <string>

class Entity {

private:
    uint32_t _uid;
    static uint32_t AvailableUid;

    std::string _name = "Default";


public:
    Entity();
    ~Entity();
    explicit Entity(const std::string& name);

    // ------------ COMPONENTS MANAGEMENT ------------
    template<typename T>
    void CreateComponent()
    {
        // TODO: Continue implementing this
    }

    template<typename T>
    T* GetComponent()
    {
        
    }

    template<typename T>
    void RemoveComponent()
    {
        // TODO: Continue implementing this
    }

    template<typename T>
    bool HasComponent()
    {

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

    friend class World;
};

#endif //COMETA_ENTITY_H
