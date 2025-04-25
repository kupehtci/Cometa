#include "Material.h"

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