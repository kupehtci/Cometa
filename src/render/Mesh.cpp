//
// Created by Daniel Laplana Gimeno on 22/4/25.
//

#include "Mesh.h"

// TODO: Delete this three references
#include "Texture.h"
#include "Shader.h"
#include "Material.h"
#include "Camera.h"

// ------------ CONSTRUCTOR AND DESTRUCTOR ------------

Mesh::Mesh()
{
    _vao = std::make_shared<VertexArray>();
}


// ------------ CUSTOM MESH METHODS ------------

void Mesh::AddVertices(float* vertices, uint32_t numVertices)
{
    _vertices.insert(_vertices.end(), vertices, vertices + numVertices);
    _numVertices += numVertices;
}

void Mesh::AddIndices(uint32_t* indices, uint32_t numIndices)
{
    _indices.insert(_indices.end(), indices, indices + numIndices);
    _numIndices += numIndices;
}


void Mesh::Build()
{
    Camera _camera = Camera();
    Shader* mainShader = new Shader("Main Shader",
        "src/render/shaders/light_map_shader.vert",
        "src/render/shaders/light_map_shader.frag");
    mainShader->Bind();

    Material _mat = Material(glm::vec3(1.0f, 1.0f, 1.0f),
                                    glm::vec3(1.0f, 0.5f, 0.31f),
                                    glm::vec3(1.0f, 0.5f, 0.31f),
                                    glm::vec3(0.5f, 0.5f, 0.5f),
                                    2.0f,
                                    "resources/bricks_diffuse_map.jpg",
                                    "resources/bricks_specular_map.jpg",
                                    "resources/black.jpg");

    Texture* materialDiffuseMap = _mat.GetDiffuseMap();
    int diffuseMapIndex = 0;
    mainShader->SetInt("material.diffuse", diffuseMapIndex);
    materialDiffuseMap->Bind(diffuseMapIndex);

    Texture* materialSpecularMap = _mat.GetSpecularMap();
    int specularMapIndex = 1;
    mainShader->SetInt("material.specular", specularMapIndex);
    materialSpecularMap->Bind(specularMapIndex);

    Texture* materialEmissionMap = _mat.GetEmissionMap();
    int emissionMapIndex = 2;
    mainShader->SetInt("material.emission", emissionMapIndex);
    materialEmissionMap->Bind(emissionMapIndex);


    mainShader->SetFloat3("material.color", _mat.GetColor());
    // mainShader->SetFloat3("material.ambient", mat.GetAmbient());
    mainShader->SetFloat3("material.diffuse", _mat.GetDiffuse());
    // mainShader->SetFloat3("material.specular", _mat.GetSpecular());
    mainShader->SetFloat("material.shininess", _mat.GetShininess());

    // glm::vec3 lightPosition = glm::vec3(glm::cos(glfwGetTime()), glm::cos(glfwGetTime()) , -2.0f);
    glm::vec3 lightPosition = glm::vec3(3.0f, 1.0f, 0.0f);

    mainShader->SetFloat3("light.position", lightPosition);
    mainShader->SetFloat3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f)/*glm::vec3(0.2f, 0.2f, 0.2f)*/);
    mainShader->SetFloat3("light.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
    mainShader->SetFloat3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

    // Update camera and its proyection
    _camera.OnUpdate();
    mainShader->SetMatrix4("uViewProjection", _camera.GetViewProyection());
    mainShader->SetFloat3("uViewPos", _camera.GetPosition());                    // Set the view position for the fragment shader


    glm::mat4 modelRotated = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    mainShader->SetMatrix4("uModel", modelRotated);

    float vertices[] = {
        // Front face
        // positions          // normals           // colors            // texture coords
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,

        // Back face
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,

        // Top face
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,

        // Bottom face
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f,

        // Right face
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,  0.0f, 0.0f,

        // Left face
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 1.0f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
        0,  1,  2,    2,  3,  0,   // Front
        4,  5,  6,    6,  7,  4,   // Back
        8,  9,  10,   10, 11, 8,   // Top
        12, 13, 14,   14, 15, 12,  // Bottom
        16, 17, 18,   18, 19, 16,  // Right
        20, 21, 22,   22, 23, 20   // Left
    };

    std::cout << "################# MESH BUILD METHOD #################" << std::endl;
    // std::cout << "vertices: " << numVertices << std::endl;
    // std::cout << "indices: " << numIndices << std::endl;
    // for (uint32_t i = 0; i < numVertices; i++)
    // {
    //     std::cout << "vertices: " << vertices[i] << std::endl;
    // }
    //
    // for (uint32_t i = 0; i < numIndices; i++)
    // {
    //     std::cout << "indices: " << indices[i] << std::endl;
    // }

    // VertexArray vao = VertexArray();
    _vao->CreateVertexBuffer(vertices, sizeof(vertices));
    _vao->CreateIndexBuffer(indices, sizeof(indices));

    _vao->GetVertexBuffers()[0]->SetLayoutBuffer({
            {0, DataType::Float3, "aPos"},
            {1, DataType::Float3, "aNormal"},
            {2, DataType::Float3, "aColor"},
            {3, DataType::Float2, "aTexCoord"}
    });
    _vao->GetVertexBuffers()[0]->GetLayoutBuffer().Bind();

    _vao->Bind();


    _vao->Bind();
    glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(indices[0]), GL_UNSIGNED_INT, 0);
    std::cout << "################# END OF MESH BUILD METHOD #################" << std::endl;
}


void Mesh::Debug()
{

    std::cout << "Vertices: " << _numVertices << std::endl;
    for (int i = 0 ; i < _numVertices ; i++)
    {
        std::cout << "Vertex ["<< i << "] : " << _vertices[i] << std::endl;
    }

    std::cout << "Indices: " << _numIndices << std::endl;
    for (int i = 0 ; i < _numIndices ; i++)
    {
        std::cout << "Indices [" << i << "] : " << _indices[i] << std::endl;
    }
}