#ifndef COMETA_MATERIAL_H
#define COMETA_MATERIAL_H

#include <glm.hpp>
#include "render/Texture.h"

/**
 * Material class that doesn't have light maps, only values
 */
class SimpleMaterial{
private:
    glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 _ambient = glm::vec3(1.0f, 0.5f, 0.32f);
    glm::vec3 _diffuse = glm::vec3(1.0f, 0.5f, 0.32f);
    glm::vec3 _specular = glm::vec3(0.5f, 0.5f, 0.5f);
    float _shininess = 256.0f;


public:
	SimpleMaterial() = default;
    SimpleMaterial(glm::vec3 color, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) :
        _color(color), _ambient(ambient), _diffuse(diffuse), _specular(specular), _shininess(shininess) {}


    // --------- GETTERS AND SETTERS ---------
    glm::vec3 GetColor() { return _color; }
    glm::vec3 GetAmbient() { return _ambient; }
    glm::vec3 GetDiffuse() { return _diffuse; }
    glm::vec3 GetSpecular() { return _specular; }
    float GetShininess() { return _shininess; }
};

/**
 * Material class with Diffuse map and Specular map
 */
class Material
{
private:
    glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 _ambient = glm::vec3(1.0f, 0.5f, 0.32f);
    glm::vec3 _diffuse = glm::vec3(1.0f, 0.5f, 0.32f);
    glm::vec3 _specular = glm::vec3(0.5f, 0.5f, 0.5f);
    float _shininess = 256.0f;

    // Maps
    Texture* _diffuseMap = nullptr;
    Texture* _specularMap = nullptr;

public:
    Material() = default;
    Material(glm::vec3 color, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) :
        _color(color), _ambient(ambient), _diffuse(diffuse), _specular(specular), _shininess(shininess) ,
        _diffuseMap(nullptr), _specularMap(nullptr){}

    Material(glm::vec3 color, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess,
        const std::string& diffuseMapPath, const std::string& specularMapPath) :
        _color(color), _ambient(ambient), _diffuse(diffuse), _specular(specular), _shininess(shininess)
    {
        LoadDiffuseMap(diffuseMapPath);
        LoadSpecularMap(specularMapPath);
    }

    // Load maps functions
    void LoadDiffuseMap(const std::string& diffuseMapPath);
    void LoadSpecularMap(const std::string& specularMapPath);


    // --------- GETTERS AND SETTERS ---------
    [[nodiscard]] glm::vec3 GetColor() const { return _color; }
    [[nodiscard]] glm::vec3 GetAmbient() const { return _ambient; }
    [[nodiscard]] glm::vec3 GetDiffuse() const { return _diffuse; }
    [[nodiscard]] glm::vec3 GetSpecular() const { return _specular; }
    [[nodiscard]] float GetShininess() const { return _shininess; }

    // Maps getters
    [[nodiscard]] inline Texture* GetDiffuseMap() const { return _diffuseMap; }
    [[nodiscard]] inline Texture* GetSpecularMap() const { return _specularMap; }
};

#endif