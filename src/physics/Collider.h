//
// Created by Daniel Laplana Gimeno on 6/5/25.
//

#ifndef COMETA_COLLIDER_H
#define COMETA_COLLIDER_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtx/quaternion.hpp>
#include <gtc/matrix_transform.hpp>
// #include <world/Components.h>

#include "physics/CollisionDispatcher.h"

// Base Collider class (abstract)
class Collider {
public:
    enum class ColliderType {
        BOX_COLLIDER = 0,
        SPHERE_COLLIDER = 1,
        COUNT = 2,
    };

    virtual ~Collider() = default;
    virtual ColliderType GetType() const = 0;
    virtual bool Intersects(const Collider* other) const = 0;
    virtual void DebugDraw() const = 0;

protected:
    Collider() = default;
};



// Box Collider implementation
class BoxCollider : public Collider {
private:
    glm::vec3 _extents = { 0.5f, 0.5f, 0.5f };
    glm::vec3 _center = { 0.0f, 0.0f, 0.0f };
    glm::quat _rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

public:
    BoxCollider() = default;
    BoxCollider(const glm::vec3& extents, const glm::vec3& center, const glm::quat& rotation)
        : _extents(extents), _center(center), _rotation(rotation) {}

    ColliderType GetType() const override { return ColliderType::BOX_COLLIDER; }

    bool Intersects(const Collider* other) const override {
        // Implement box-box and box-sphere intersection
        return false; // Placeholder
    }

    void DebugDraw() const override {
        // Implement debug visualization
    }

    // Getters and setters
    const glm::vec3& GetExtents() const { return _extents; }
    const glm::vec3& GetCenter() const { return _center; }
    const glm::quat& GetRotation() const { return _rotation; }

    void SetExtents(const glm::vec3& extents) { _extents = extents; }
    void SetCenter(const glm::vec3& center) { _center = center; }
    void SetRotation(const glm::quat& rotation) { _rotation = rotation; }
};

// Sphere Collider implementation
class SphereCollider : public Collider {
private:
    float _radius = 0.5f;
    glm::vec3 _center = { 0.0f, 0.0f, 0.0f };

public:
    SphereCollider() = default;
    SphereCollider(float radius, const glm::vec3& center)
        : _radius(radius), _center(center) {}

    ColliderType GetType() const override { return ColliderType::SPHERE_COLLIDER; }

    bool Intersects(const Collider* other) const override {
        // Implement sphere-sphere and sphere-box intersection
        return false; // Placeholder
    }

    void DebugDraw() const override {
        // Implement debug visualization
    }

    // Getters and setters
    float GetRadius() const { return _radius; }
    const glm::vec3& GetCenter() const { return _center; }

    void SetRadius(float radius) { _radius = radius; }
    void SetCenter(const glm::vec3& center) { _center = center; }
};


#endif //COMETA_COLLIDER_H
