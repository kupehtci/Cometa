#ifndef COMETA_ENTITY_H
#define COMETA_ENTITY_H

#include <string>

class Entity {

private:
    uint32_t _uid;
    static uint32_t AvailableUid;

    std::string _name = "Default";

    // keep private if only World class should instantiate and manage instances
    Entity();
    explicit Entity(const std::string& name);

public:
    ~Entity();

public:
    // --------- GETTERS AND SETTERS ---------
    [[nodiscard]] uint32_t GetUID() const { return _uid;}
    [[nodiscard]] std::string GetName() const { return _name;}

    friend class World;
};

#endif //COMETA_ENTITY_H
