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

/**
 * Model class is an interface to load Meshes and materials using Assimp library.
 * By creating a mesh:
 *      Mesh mesh("path/to/model.fbx")
 *
 * You can retrieve easily the models contained
 */
class Model {
private:
    // Meshed that compose the model
    std::vector<std::shared_ptr<Mesh>> _meshes;

    // directory from where the model is loaded
    // is needed for material loading
    std::string _directory;

    // relative path of the model file
    std::string _path;

    /**
     * Load the model from a file
     * @param path Relative path to the file that define the 3D model 
     */
    void LoadModel(const std::string& path);

    /**
     * Process a node from the loaded model
     * @param node node of the model
     * @param scene assimp scene to process the node
     */
    void ProcessNode(aiNode* node, const aiScene* scene);

    /**
     * Process a single mesh from a node.
     * @param mesh mesh pointer from the assimp mess retrieved from the model's node
     * @param scene assimp scene pointer
     * @return Shared pointer to the Cometa's mesh
     */
    std::shared_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);

    /**
     * Load the materials attached to the model
     * @param mat Assimp's material loaded from the model
     * @param type Type of assimp's texture
     * @param material shared pointer to the material that will be binded with the assimp's material data
     */
    void LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::shared_ptr<Material>& material);

public:
    /**
     * Model constructor
     * @param path path to the model to load
     */
    explicit Model(const std::string& path);
    ~Model() = default;

    /**
     * Draw the model
     * this Method is not in use, but allow to render directly from the model
     */
    void Draw();

    /**
     * Retrieve the Meshes that compose the model
     * @return Vector of shared pointers containing the meshes
     */
    [[nodiscard]] std::vector<std::shared_ptr<Mesh>> GetMeshes() const { return _meshes; }
};

#endif //COMETA_MODEL_H 