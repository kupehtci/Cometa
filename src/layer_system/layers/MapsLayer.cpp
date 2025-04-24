//
// Created by Daniel Laplana Gimeno on 18/4/25.
//

#include "MapsLayer.h"

#include "render/Renderer.h"
#include "render/Shader.h"
#include "render/Mesh.h"

#include "world/Entity.h"
#include "world/World.h"
#include "world/Components.h"



MapsLayer::MapsLayer()
{

}

MapsLayer::~MapsLayer()
{

}

void MapsLayer::Init()
{
    _texture = new Texture("./resources/macos_example.jpg");
    _camera = Camera();

    _mat = Material(glm::vec3(1.0f, 1.0f, 1.0f),
                                    glm::vec3(1.0f, 0.5f, 0.31f),
                                    glm::vec3(1.0f, 0.5f, 0.31f),
                                    glm::vec3(0.5f, 0.5f, 0.5f),
                                    2.0f,
                                    "resources/bricks_diffuse_map.jpg",
                                    "resources/bricks_specular_map.jpg",
                                    "resources/black.jpg");

    World world0 = World();
    Entity* ent0 = world0.CreateEntity("Entity0");
    Renderable* rend = ent0->CreateComponent<Renderable>();

    ent0->CreateComponent<Collider>();

    if (ent0->HasComponent<Transform>())
    {
        std::cout << "Has transform ent0 " << std::endl;
    }

    if (ent0->HasComponent<Renderable>())
    {
        std::cout << "Has renderable ent0 " << std::endl;
    }

    if (ent0->HasComponent<SpriteRenderable>())
    {
        std::cout << "Has sprite renderable ent0 " << std::endl;
    }

    if (ent0->HasComponent<Collider>())
    {
        std::cout << "Has collider ent0 " << std::endl;
    }

    Entity* ent1 = world0.CreateEntity("Entity1");
    

    // Debug the world created
    world0.DebugPrint();
}

void MapsLayer::Update()
{
    Shader* mainShader = new Shader("Main Shader",
        "src/render/shaders/light_map_shader.vert",
        "src/render/shaders/light_map_shader.frag");
    mainShader->Bind();

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

    Mesh mesh0 = Mesh();
    mesh0.AddVertices(vertices, sizeof(vertices) / sizeof(float));
    mesh0.AddIndices(indices, sizeof(indices) / sizeof(uint32_t));
    mesh0.SetLayoutBuffer(
    {
        {0, DataType::Float3, "aPos"},
        {1, DataType::Float3, "aNormal"},
        {2, DataType::Float3, "aColor"},
        {3, DataType::Float2, "aTexCoord"}
        });
    mesh0.Build();

    mesh0.Draw();


    // ------------------ DRAW MORE CUBES ---------------------------
    for (int i = 0; i < 6; i++)
    {
        mainShader->SetMatrix4("uModel", glm::translate(glm::mat4(1.0f), glm::vec3(1.0f + i, 0.0f, -4.0f - i)));
        mesh0.Draw();
    }

    for (int i = 0; i < 6; i++)
    {
        mainShader->SetMatrix4("uModel", glm::translate(glm::mat4(1.0f), glm::vec3(1.0f + i, 1.0f, -5.0f - i)));
        mesh0.Draw();
    }
    // ------------------ END OF DRAWING MORE CUBES ---------------------------


    mainShader->Unbind();


    // --------- Draw LIGHT POINT ---------

    Shader* lightShader = new Shader("Light Shader", "src/render/shaders/light_shader.vert", "src/render/shaders/light_shader.frag");
    lightShader->Bind();

    lightShader->SetMatrix4("uViewProjection", _camera.GetViewProyection());
    glm::mat4 lightPosMatrix = glm::translate(glm::mat4(1.0f), lightPosition);
    lightPosMatrix = glm::scale(lightPosMatrix, glm::vec3(0.2f, 0.2f, 0.2f));

    lightShader->SetMatrix4("uModel", lightPosMatrix);

    mesh0.Bind();
    mesh0.Draw();
    //glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);

    lightShader->Unbind();

    // --------- END OF DRAWING LIGHT POINT ---------
}


void MapsLayer::Close()
{

}

void MapsLayer::HandleEvent(Event& event){

}