#ifndef COMETA_COMPONENTS_H
#define COMETA_COMPONENTS_H

#include <iostream>
#include <string>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtx/quaternion.hpp>
#include <gtc/matrix_transform.hpp>
#include <utility>

#include "render/Texture.h"
#include "render/Mesh.h"
#include "render/Material.h"

class Entity;
class Renderer;

/**
 * Component virtual class
 */
class Component {
private:
	Entity* _owner = nullptr;

public:
	virtual ~Component() = default;

	// ------------ GETTERS AND SETTERS ------------
	[[nodiscard]] Entity* GetOwner() const { return _owner; }
	void SetOwner(Entity* newOwner) { _owner = newOwner; }

	friend class Entity;
	friend class ComponentRegistry;
};

class Transform : public Component {
public: 

	glm::vec3 position = { 0.0f, 0.0f, 0.0f }; 
	glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
	glm::vec3 scale = { 1.0f, 1.0f, 1.0f }; 

	Transform() = default;
	explicit Transform(const glm::vec3& position)
	{
		this->position = position;
		this->rotation = { 0.0f, 0.0f, 0.0f };
		this->scale = { 1.0f, 1.0f, 1.0f };
	}
	Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : position(position), rotation(rotation), scale(scale) {};
	Transform(const Transform& other)
	{
		position = other.position;
		rotation = other.rotation;
		scale = other.scale;
	};

	[[nodiscard]] glm::mat4 GetTransform() const {
		const glm::mat4 rotation = glm::toMat4(glm::quat(glm::radians(this->rotation)));
		return glm::translate(glm::mat4(1.0f), position) * rotation * glm::scale(glm::mat4(1.0f), scale);
	}

	friend std::ostream& operator<<(std::ostream& os, const Transform& transform)
	{
		os << "  - Transform: "
						  << "Pos(" << transform.position.x << ", "
						  << transform.position.y << ", "
						  << transform.position.z << "), "
						  << "Rot(" << transform.rotation.x << ", "
						  << transform.rotation.y << ", "
						  << transform.rotation.z << "), "
						  << "Scale(" << transform.scale.x << ", "
						  << transform.scale.y << ", "
						  << transform.scale.z << ")" << std::endl;
		return os;
	}
};

class MeshRenderable : public Component {
private:
	std::shared_ptr<Mesh> _mesh = nullptr;
	std::shared_ptr<Material> _material = nullptr;

public:
	MeshRenderable() = default;
	MeshRenderable(const MeshRenderable&) = default;

	// Properties management methods

	void SetMesh(const std::shared_ptr<Mesh>& mesh) { _mesh = mesh; }
	void SetMaterial(const std::shared_ptr<Material>& material) {_material = material;}

	// ------------ GETTERS ------------
	[[nodiscard]] std::shared_ptr<Mesh> GetMesh() const { return _mesh; }
	[[nodiscard]] std::shared_ptr<Material> GetMaterial() const { return _material; }
};


class SpriteRenderable : public Component {
public: 
	Texture texture; 
	glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

	SpriteRenderable() = default;
	SpriteRenderable(const SpriteRenderable&) = default;
};


class PointLight : public Component{
	friend class Renderer;
private:
	glm::vec3 _ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	glm::vec3 _diffuse = glm::vec3(0.7f, 0.7f, 0.7f);
	glm::vec3 _specular = glm::vec3(1.0f, 1.0f, 1.0f);

	float _constant = 1.0f;
	float _linear = 0.07f;
	float _quadratic = 0.017f;

public:
	PointLight() = default;
	PointLight(const PointLight&) = default;

	PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic):
		_ambient(ambient), _diffuse(diffuse), _specular(specular), _constant(constant), _linear(linear), _quadratic(quadratic) {};

	// ------ GETTERS ---------
	[[nodiscard]] glm::vec3 GetAmbient() const { return _ambient; }
	[[nodiscard]] glm::vec3 GetDiffuse() const { return _diffuse; }
	[[nodiscard]] glm::vec3 GetSpecular() const { return _specular; }
	[[nodiscard]] float GetConstant() const { return _constant; }
	[[nodiscard]] float GetLinear() const { return _linear; }
	[[nodiscard]] float GetQuadratic() const { return _quadratic; }

	// ------ SETTERS ------
	void SetAmbient(const glm::vec3& ambient) { _ambient = ambient; }
	void SetDiffuse(const glm::vec3& diffuse) { _diffuse = diffuse; }
	void SetSpecular(const glm::vec3& specular) { _specular = specular; }
	void SetConstant(float constant) { _constant = constant; }
	void SetLinear(float linear) { _linear = linear; }
	void SetQuadratic(float quadratic) { _quadratic = quadratic; }
};

class DirectionalLight : public Component
{
	friend class Renderer;
private:
	glm::vec3 _direction = glm::vec3(-0.2f, -1.0f, -0.3f);
	glm::vec3 _ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	glm::vec3 _diffuse = glm::vec3(0.35f, 0.4f, 0.35f);
	glm::vec3 _specular = glm::vec3(0.5f, 0.5f, 0.5f);

public:
	DirectionalLight() = default;
	DirectionalLight(const DirectionalLight&) = default;

	// --------- GETTERS ---------
	[[nodiscard]] glm::vec3 GetDirection() const { return _direction; }
	[[nodiscard]] glm::vec3 GetAmbient() const { return _ambient; }
	[[nodiscard]] glm::vec3 GetDiffuse() const { return _diffuse; }
	[[nodiscard]] glm::vec3 GetSpecular() const { return _specular; }

	// --------- SETTERS ---------
	void SetDirection(const glm::vec3& direction) { _direction = direction; }
	void SetAmbient(const glm::vec3& ambient) { _ambient = ambient; }
	void SetDiffuse(const glm::vec3& diffuse) { _diffuse = diffuse; }
	void SetSpecular(const glm::vec3& specular) { _specular = specular; }
};

class Collider : public Component {
public: 
	Collider() = default;
	Collider(const Collider&) = default;
};

class RigidBody : public Component
{
public:
	glm::vec3 linearVelocity = { 0.0f, 0.0f, 0.0f };
	glm::vec3 angularVelocity = { 0.0f, 0.0f, 0.0f };
	float mass = 1.0f;

	RigidBody() = default;
};

class Tag : public Component {
private: 
	std::string _tag = ""; 
public: 
	Tag() = default;
	Tag(const Tag&) = default;
	explicit Tag(std::string  tag) : _tag(std::move(tag)) {}

	std::string GetTag() { return _tag;  }
	void SetTag(const std::string& tag) { _tag = tag; }
};

#endif