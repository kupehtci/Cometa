#include "Material.h"


// Load maps methods
void Material::LoadDiffuseMap(const std::string& diffuseMapPath)
{
    _diffuseMap = new Texture(diffuseMapPath);
}
void Material::LoadSpecularMap(const std::string& specularMapPath)
{
    _specularMap = new Texture(specularMapPath);
}

void Material::LoadEmissionMap(const std::string& emissionMapPath)
{
    _emissionMap = new Texture(emissionMapPath);
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

}