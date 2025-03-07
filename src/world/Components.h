#ifndef COMETA_COMPONENTS_H
#define COMETA_COMPONENTS_H

#include "Entity.h"
#include "render/Texture.h"

#include <stdio.h>
#include <string>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtx/quaternion.hpp>
#include <gtc/matrix_transform.hpp>

class Component {
protected: 
	// Entity* _owner; 
};

class TransformComponent : public Component {
public: 

	glm::vec3 translation = { 0.0f, 0.0f, 0.0f }; 
	glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
	glm::vec3 scale = { 1.0f, 1.0f, 1.0f }; 

	TransformComponent() = default; 
	TransformComponent(const TransformComponent&) = default; 
	TransformComponent(const glm::vec3& translation) {
		this->translation = translation; 
	}

	glm::mat4 GetTransform() {

		glm::mat4 rotation = glm::toMat4(glm::quat(this->rotation));
		return glm::translate(glm::mat4(1.0f), translation) * rotation * glm::scale(glm::mat4(1.0f), scale);
	}
	
};

class RendererComponent : public Component {
	RendererComponent() = default; 
	RendererComponent(const RendererComponent&) = default; 
};

class SpriteRendererComponent : public Component {
public: 
	Texture texture; 
	glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

	SpriteRendererComponent() = default;
	SpriteRendererComponent(const SpriteRendererComponent&) = default;
};

class ColliderComponent : public Component {
public: 
	ColliderComponent() = default; 
	ColliderComponent(const ColliderComponent&) = default;
};

class TagComponent : public Component {
private: 
	std::string _tag = ""; 
public: 
	TagComponent() = default;
	TagComponent(const TagComponent&) = default;
	TagComponent(const std::string& tag) : _tag(tag) {}

	std::string GetTag() { return _tag;  }
	void SetTag(const std::string& tag) { _tag = tag; }
};

#endif