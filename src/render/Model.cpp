#include "Model.h"
#include <iostream>
#include <filesystem>

Model::Model(const std::string& path) {
    _path = "";
    _directory = "";
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

    _path = path;
    _directory = std::filesystem::path(path).parent_path().string();
    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene) {

    // Iterate over model's meshes
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        _meshes.push_back(ProcessMesh(mesh, scene));
    }

    // iterate over the meshes childs
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene);
    }
}

std::shared_ptr<Mesh> Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    // Process vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        // positions
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);

        // normals
        if (mesh->HasNormals()) {
            vertices.push_back(mesh->mNormals[i].x);
            vertices.push_back(mesh->mNormals[i].y);
            vertices.push_back(mesh->mNormals[i].z);
        } else {
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
        }

        // set default color
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);
        vertices.push_back(1.0f);

        // texture coordinates
        if (mesh->mTextureCoords[0]) {
            vertices.push_back(mesh->mTextureCoords[0][i].x);
            vertices.push_back(mesh->mTextureCoords[0][i].y);
        } else {
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
        }
    }

    // Process the indices of the model
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Create mesh object
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
        
        // Load textures for different types
        LoadMaterialTextures(material, aiTextureType_DIFFUSE, meshMaterial);
        LoadMaterialTextures(material, aiTextureType_SPECULAR, meshMaterial);
        LoadMaterialTextures(material, aiTextureType_EMISSIVE, meshMaterial);
        
        meshMaterial->LoadShader("Main Shader",
            "src/render/shaders/blinn_phong_shader.vert",
            "src/render/shaders/blinn_phong_shader.frag");

        // Store the material with the mesh
        _materials[resultMesh] = meshMaterial;
    }

    // // Process material
    // if (mesh->mMaterialIndex >= 0) {
    //     aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    //     std::shared_ptr<Material> meshMaterial = std::make_shared<Material>();
        
    //     // Load material textures
    //     LoadMaterialTextures(material, aiTextureType_DIFFUSE, meshMaterial);
    //     LoadMaterialTextures(material, aiTextureType_SPECULAR, meshMaterial);
    //     LoadMaterialTextures(material, aiTextureType_EMISSIVE, meshMaterial);
    //     LoadMaterialTextures(material, aiTextureType_NORMALS, meshMaterial);

    //     // Extract material properties
    //     aiColor3D color(0.0f, 0.0f, 0.0f);
    //     if(material->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS) {
    //         meshMaterial->SetColor(glm::vec3(color.r, color.g, color.b));
    //     }

    //     float shininess = 0.0f;
    //     if(material->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS) {
    //         meshMaterial->SetShininess(shininess);
    //     }

    //     // Assign material to mesh
    //     resultMesh->SetMaterial(meshMaterial);
    // }

    // return resultMesh;
}

void Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::shared_ptr<Material>& material) {
    // Load material properties
    aiColor3D color(0.f, 0.f, 0.f);
    aiColor3D ambient(0.f, 0.f, 0.f);
    aiColor3D diffuse(0.f, 0.f, 0.f);
    aiColor3D specular(0.f, 0.f, 0.f);
    float shininess = 0.0f;

    // Extract material properties
    if(mat->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS) {
        material->SetColor(glm::vec3(color.r, color.g, color.b));
    }
    if(mat->Get(AI_MATKEY_COLOR_AMBIENT, ambient) == AI_SUCCESS) {
        material->SetAmbient(glm::vec3(ambient.r, ambient.g, ambient.b));
    }
    if(mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse) == AI_SUCCESS) {
        material->SetDiffuse(glm::vec3(diffuse.r, diffuse.g, diffuse.b));
    }
    if(mat->Get(AI_MATKEY_COLOR_SPECULAR, specular) == AI_SUCCESS) {
        material->SetSpecular(glm::vec3(specular.r, specular.g, specular.b));
    }
    if(mat->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS) {
        material->SetShininess(shininess);
    }

    // Load material textures
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