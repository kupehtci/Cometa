#ifndef COMETA_COMPONENTS_H
#define COMETA_COMPONENTS_H

#include "render/Texture.h"

#include <iostream>
#include <string>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtx/quaternion.hpp>
#include <gtc/matrix_transform.hpp>

class Entity;

class Component {
public: 
	virtual ~Component() = default;
public:
	Entity* _owner = nullptr;

	
	// GETTERS AND SETTERS
	Entity* GetOwner() { return _owner; }
	

	friend class Entity;
	friend class ComponentRegistry;
};

class Transform : public Component {
public: 

	glm::vec3 translation = { 0.0f, 0.0f, 0.0f }; 
	glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
	glm::vec3 scale = { 1.0f, 1.0f, 1.0f }; 

	Transform() = default;
	Transform(const Transform& other)
	{
		translation = other.translation;
		rotation = other.rotation;
		scale = other.scale;
	};

	explicit Transform(const glm::vec3& translation) {
		this->translation = translation;
		this->rotation = { 0.0f, 0.0f, 0.0f };
		this->scale = { 1.0f, 1.0f, 1.0f };
	}

	[[nodiscard]] glm::mat4 GetTransform() const {
		const glm::mat4 rotation = glm::toMat4(glm::quat(this->rotation));
		return glm::translate(glm::mat4(1.0f), translation) * rotation * glm::scale(glm::mat4(1.0f), scale);
	}

	friend std::ostream& operator<<(std::ostream& os, const Transform& transform)
	{
		os << "owner: "	 << "Transform";
		return os;
	}
};

class Renderable : public Component {
public:
	Renderable() = default;
	Renderable(const Renderable&) = default;
};

class SpriteRenderable : public Component {
public: 
	Texture texture; 
	glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

	SpriteRenderable() = default;
	SpriteRenderable(const SpriteRenderable&) = default;
};

class Collider : public Component {
public: 
	Collider() = default;
	Collider(const Collider&) = default;
};

class RigidBody : public Component
{
public:
	RigidBody() = default;
};

class Tag : public Component {
private: 
	std::string _tag = ""; 
public: 
	Tag() = default;
	Tag(const Tag&) = default;
	Tag(const std::string& tag) : _tag(tag) {}

	std::string GetTag() { return _tag;  }
	void SetTag(const std::string& tag) { _tag = tag; }
};

#endif