#include "Model.h"
#include <iostream>
#include <filesystem>

Model::Model(const std::string& path, bool gamma) : _gammaCorrection(gamma) {
    LoadModel(path);
}

void Model::LoadModel(const std::string& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, 
        aiProcess_Triangulate | 
        aiProcess_GenNormals | 
        aiProcess_CalcTangentSpace |
        aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    _directory = std::filesystem::path(path).parent_path().string();
    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene) {
    // Process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        _meshes.push_back(ProcessMesh(mesh, scene));
    }

    // Then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene);
    }
}

std::shared_ptr<Mesh> Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    // Process vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        // Position
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);

        // Normal
        if (mesh->HasNormals()) {
            vertices.push_back(mesh->mNormals[i].x);
            vertices.push_back(mesh->mNormals[i].y);
            vertices.push_back(mesh->mNormals[i].z);
        } else {
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
        }

        // Color (default white)
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);

        // Texture Coordinates
        if (mesh->mTextureCoords[0]) {
            vertices.push_back(mesh->mTextureCoords[0][i].x);
            vertices.push_back(mesh->mTextureCoords[0][i].y);
        } else {
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
        }
    }

    // Process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Create mesh
    std::shared_ptr<Mesh> resultMesh = std::make_shared<Mesh>();
    resultMesh->AddVertices(vertices.data(), vertices.size());
    resultMesh->AddIndices(indices.data(), indices.size());
    resultMesh->SetLayoutBuffer({
        {0, DataType::Float3, "aPos"},
        {1, DataType::Float3, "aNormal"},
        {2, DataType::Float3, "aColor"},
        {3, DataType::Float2, "aTexCoord"}
    });
    resultMesh->Build();

    // Process material
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::shared_ptr<Material> meshMaterial = std::make_shared<Material>();
        
        // Load material textures
        LoadMaterialTextures(material, aiTextureType_DIFFUSE, meshMaterial);
        LoadMaterialTextures(material, aiTextureType_SPECULAR, meshMaterial);
        LoadMaterialTextures(material, aiTextureType_EMISSIVE, meshMaterial);
    }

    return resultMesh;
}

void Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::shared_ptr<Material>& material) {
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        
        std::string texturePath = _directory + "/" + str.C_Str();
        
        switch (type) {
            case aiTextureType_DIFFUSE:
                material->LoadDiffuseMap(texturePath);
                break;
            case aiTextureType_SPECULAR:
                material->LoadSpecularMap(texturePath);
                break;
            case aiTextureType_EMISSIVE:
                material->LoadEmissionMap(texturePath);
                break;
            default:
                break;
        }
    }
}

void Model::Draw() {
    for (auto& mesh : _meshes) {
        mesh->Draw();
    }
} 