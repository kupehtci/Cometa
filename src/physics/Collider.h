
#ifndef COMETA_COLLIDER_H
#define COMETA_COLLIDER_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtx/quaternion.hpp>
#include <gtc/matrix_transform.hpp>
// #include <world/Components.h>

#include <iostream>
#include <ostream>

#include "physics/CollisionDispatcher.h"

/**
 * Abstract base class for the different collider shapes of Cometa
 */
class Collider {
public:
    /**
     * Collider type enumerator
     * In case of adding new types of shapes, add an enumerator here and update CollisionDispatch class.
     */
    enum class ColliderType {
        BOX_COLLIDER = 0,
        SPHERE_COLLIDER = 1,
        COUNT = 2,
    };

    virtual ~Collider() = default;

    /**
     * Get the type of the collider.
     * Each Collider derived class needs to implement this method and return the appropriate type of collider
     * Helps to check the collider type by having a @code {Collider* collider ...}
     * @return {ColliderType} of the actual collider object.
     */
    [[nodiscard]] virtual ColliderType GetType() const = 0;

    /**
     * Virtual function that need to be implemented on each derived class and returns the inertia tensor of the type of shape defined by the collider
     * @param mass {float} Mass of the entity associated.
     * @return {mat3} Inertia tensor of the shape
     */
    virtual glm::mat3 CalculateInertiaTensor(float mass) = 0;

    /**
     * Virtual function that need to be implemented on each derived class and returns the inverse inertia tensor of the type of shape defined by the collider
     * The inverse inertia tensor avoid unnecessary calculations on each frame
     * @param mass {float} Mass of the entity associated.
     * @return {mat3} Inverse Inertia tensor of the shape
     */
    virtual glm::mat3 CalculateInverseInertiaTensor(float mass) = 0;

protected:
    /**
     * Collider default contructor
     */
    Collider() = default;
};


/**
 * Collider that represents a Box.
 * A box is defined by its extents or halfside of each side of the box,
 * the center offset in comparison with the transform position and the rotation stored as a quaterion
 * that represents the rotation difference with the entity's tranform rotation
 */
class BoxCollider : public Collider {
private:
    glm::vec3 _extents = { 0.5f, 0.5f, 0.5f };
    glm::vec3 _center = { 0.0f, 0.0f, 0.0f };
    glm::quat _rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);


public:
    /**
     * Box collider default constructor
     */
    BoxCollider() = default;

    /**
     * BoxCollider constructor with extents
     * @param extents {vec3} 3D vector that represents the extents of the box
     */
    explicit BoxCollider(const glm::vec3& extents)
        : _extents(extents), _center({0.0f, 0.0f, 0.0f}) {}

    /**
     * BoxCollider constructor that passes as arguments the extents and center offset
     * Rotation keeps as an identity matrix with no rotation.
     * @param extents {vec3} extents or halfsize of the box
     * @param center {vec3} offset center between the collider and the transform
     */
    BoxCollider(const glm::vec3& extents, const glm::vec3& center)
    : _extents(extents), _center(center)
    {
        std::cout << "BoxCollider constructor called" << std::endl;
    }

    /**
     * BoxCollider constructor that passes as arguments the extents, center offset and the rotation of the box.
     * @param extents {vec3} extents or halfsize of the box
     * @param center {vec3} offset center between the collider and the transform
     */
    BoxCollider(const glm::vec3& extents, const glm::vec3& center, const glm::quat& rotation)
        : _extents(extents), _center(center), _rotation(rotation) {}

    /**
     * Return ColliderType::BOX_COLLIDER as the type of this collider
     */
    [[nodiscard]] ColliderType GetType() const override { return ColliderType::BOX_COLLIDER; }

    /**
     * Calculate inertia tensor of the Box
     * @param mass {float} mass of the entity
     * @return {mat3} inertia tensor
     */
    glm::mat3 CalculateInertiaTensor(float mass) override
    {
        // Calculate dimensions
        glm::vec3 size = GetSize();

        // Calculate local inertia tensor for a box
        float x2 = size.x * size.x;
        float y2 = size.y * size.y;
        float z2 = size.z * size.z;
        glm::mat3 inertiaTensor {};
        // Initialize with identity matrix
        inertiaTensor = glm::mat3(1.0f);

        // Set diagonal elements (mass will be multiplied later)
        inertiaTensor[0][0] = (y2 + z2) / 12.0f;  // Ixx
        inertiaTensor[1][1] = (x2 + z2) / 12.0f;  // Iyy
        inertiaTensor[2][2] = (x2 + y2) / 12.0f;  // Izz

        return inertiaTensor;
    }

    /**
     * Calculates the inverse inertia tensor of the box
     * @param mass {float} mass of the object
     * @return {mat3} inverse inertia tensor
     */
    glm::mat3 CalculateInverseInertiaTensor(float mass) override
    {
        glm::vec3 size = GetSize();

        float x2 = size.x * size.x;
        float y2 = size.y * size.y;
        float z2 = size.z * size.z;
        glm::mat3 inertiaTensor = glm::mat3(1.0f);
        inertiaTensor[0][0] = (y2 + z2) / 12.0f;
        inertiaTensor[1][1] = (x2 + z2) / 12.0f;
        inertiaTensor[2][2] = (x2 + y2) / 12.0f;

        return glm::inverse(inertiaTensor);
    }

    // Getters and setters

    /**
     * @return {vec3} extents of the box
     */
    [[nodiscard]] const glm::vec3& GetExtents() const { return _extents; }

    /**
     * @return {vec3} total size of the box (extents * 2)
     */
    [[nodiscard]] glm::vec3 GetSize() const { return _extents * 2.0f; }

    /**
     * @return {vec3} center offset of the box collider
     */
    [[nodiscard]] const glm::vec3& GetCenter() const { return _center; }

    /**
     * @return {quat} rotation quaternion of the box collider
     */
    [[nodiscard]] const glm::quat& GetRotation() const { return _rotation; }

    /**
     * Set the extents for the box collider
     * @param extents {vec3} new extents value
     */
    void SetExtents(const glm::vec3& extents) { _extents = extents; }

    /**
     * Set the center offset of the box collider
     * @param center {vec3} new center offset
     */
    void SetCenter(const glm::vec3& center) { _center = center; }

    /**
     * Set the new rotation for the box collider
     * @param rotation {quat}
     */
    void SetRotation(const glm::quat& rotation) { _rotation = rotation; }
};

/**
 * Collider that represents an sphere shape defined
 */
class SphereCollider : public Collider {
private:
    float _radius = 0.5f;
    glm::vec3 _center = { 0.0f, 0.0f, 0.0f };

public:
    /**
     * Sphere collider default constructor
     */
    SphereCollider() = default;
    explicit SphereCollider(float radius)
        : _radius(radius), _center({0.0f, 0.0f, 0.0f}) { }
    SphereCollider(float radius, const glm::vec3& center)
        : _radius(radius), _center(center) {}

    /**
     * Return ColliderType::SPHERE_COLLIDER as the type of collider from Sphere Collider
     */
    [[nodiscard]] ColliderType GetType() const override { return ColliderType::SPHERE_COLLIDER; }


    /**
     * Return the inertia tensor for a solid sphere
     * @param mass {float} mass of the entity to calculate the inertia tensor
     * @return {mat3} inertia tensor
     */
    glm::mat3 CalculateInertiaTensor(float mass) override
    {
        const float i = (2.0f * _radius * _radius) / 5.0f;

        const auto inertiaTensor = glm::mat3(
            i, 0.0f, 0.0f,
            0.0f, i, 0.0f,
            0.0f, 0.0f, i
        );
        return inertiaTensor;
    }

    /**
     * Calculate the inverse inertia tensor of a solid sphere
     * @param mass {flaot} mass of the entity to calculate the inverse inertia tensor
     * @return {mat3} inertia tensor
     */
    glm::mat3 CalculateInverseInertiaTensor(float mass) override
    {
        float i = (2.0f * _radius * _radius) / 5.0f;

        glm::mat3 inverseInertiaTensor {};
        inverseInertiaTensor = glm::mat3(
            1.0f/i, 0.0f, 0.0f,
            0.0f, 1.0f/i, 0.0f,
            0.0f, 0.0f, 1.0f/i
        );
        return inverseInertiaTensor;
    }


    // ---------- Getters and setters ----------

    /**
     * @return {float} radius of the sphere
     */
    [[nodiscard]] float GetRadius() const { return _radius; }

    /**
     * @return {vec3} center offset of the sphere
     */
    [[nodiscard]] const glm::vec3& GetCenter() const { return _center; }

    /**
     * Set the new radius for the sphere
     * @param radius {float} new radius of the sphere
     */
    void SetRadius(const float radius) { _radius = radius; }

    /**
     * Set the center offset of the sphere
     * @param center {vec3} new center offset of the sphere
     */
    void SetCenter(const glm::vec3& center) { _center = center; }
};


#endif //COMETA_COLLIDER_H
