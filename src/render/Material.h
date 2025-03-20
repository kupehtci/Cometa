#ifndef COMETA_MATERIAL_H
#define COMETA_MATERIAL_H

#include <glm.hpp>

class Material{
private: 
    glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 _ambient = glm::vec3(1.0f, 0.5f, 0.32f); 
    glm::vec3 _diffuse = glm::vec3(1.0f, 0.5f, 0.32f);
    glm::vec3 _specular = glm::vec3(0.5f, 0.5f, 0.5f);
    float _shininess = 256.0f;

public:
	Material() = default; 
    Material(glm::vec3 color, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) :
        _color(color), _ambient(ambient), _diffuse(diffuse), _specular(specular), _shininess(shininess) {}


    // --------- GETTERS AND SETTERS ---------
    glm::vec3 GetColor() { return _color; }
    glm::vec3 GetAmbient() { return _ambient; }
    glm::vec3 GetDiffuse() { return _diffuse; }
    glm::vec3 GetSpecular() { return _specular; }
    float GetShininess() { return _shininess; }
};

#endif