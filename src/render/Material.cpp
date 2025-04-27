#include "Material.h"


// Load maps methods
void Material::LoadDiffuseMap(const std::string& diffuseMapPath)
{
    _diffuseMap = std::make_shared<Texture>(diffuseMapPath);
}
void Material::LoadSpecularMap(const std::string& specularMapPath)
{
    _specularMap = std::make_shared<Texture>(specularMapPath);
}

void Material::LoadEmissionMap(const std::string& emissionMapPath)
{
    _emissionMap = std::make_shared<Texture>(emissionMapPath);
}

void Material::LoadShader(const Shader& shader)
{
    _shader = std::make_shared<Shader>(shader);
}
void Material::LoadShader(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    // _shader = std::make_shared<Shader>(name, vertexShaderPath, fragmentShaderPath);
    _shader = Shader::LoadShader(name, vertexShaderPath, fragmentShaderPath);
}
void Material::UnsetShader()
{
    _shader = nullptr;
}

// Rendering methods

/**
 * Binds imply to setting all the GPU uniforms and structures with the data stored in the object
 */
void Material::Bind(){

}