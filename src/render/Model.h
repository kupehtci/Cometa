#ifndef COMETA_MODEL_H
#define COMETA_MODEL_H

#include <string>
#include <vector>
#include <memory>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "render/Mesh.h"
#include "render/Material.h"

class Model {
private:
    std::vector<std::shared_ptr<Mesh>> _meshes;
    std::string _directory;
    bool _gammaCorrection;

    void LoadModel(const std::string& path);
    void ProcessNode(aiNode* node, const aiScene* scene);
    std::shared_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
    void LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::shared_ptr<Material>& material);

public:
    Model(const std::string& path, bool gamma = false);
    ~Model() = default;

    void Draw();
    std::vector<std::shared_ptr<Mesh>> GetMeshes() const { return _meshes; }
};

#endif //COMETA_MODEL_H 