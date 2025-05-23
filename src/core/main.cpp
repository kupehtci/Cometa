//
//// #define GLFW_INCLUDE_VULKAN
//

#include "../core/Application.h"

#include <filesystem>
#include <iostream>

// #include "../debug/Assertion.h"

#include "world/Components.h"
#include "world/Entity.h"
#include "render/Shader.h"

int main() {

    // Application* app = Application::GetInstancePtr();
    // app->Init();
    // app->Running();
    // app->Close();
    //
    // delete app;

    Renderer::Create();
    Renderer* _renderer = Renderer::GetInstancePtr();

    Input::Create();
    Input* _input = Input::GetInstancePtr();

    _renderer->Init();
    _input->Init();

    // INitialize main components
    Camera* currentCamera = new Camera();


    auto brickMaterial = std::make_shared<Material>(glm::vec3(1.0f, 1.0f, 1.0f),
                                    glm::vec3(1.0f, 0.5f, 0.31f),
                                    glm::vec3(1.0f, 0.5f, 0.31f),
                                    glm::vec3(0.5f, 0.5f, 0.5f),
                                    64.0f,
                                    "resources/bricks_diffuse_map.jpg",
                                    "resources/white.jpg",
                                    "resources/black.jpg");

    brickMaterial->LoadShader("Blinn phong shader",
        "src/render/shaders/light_map_shader.vert",
    "src/render/shaders/light_map_shader.frag" );
    brickMaterial->Bind();

    // Geometry definition
    float vertices[] = {
        // positions          // normals           // colors            // texture coords
        // Front face
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


    std::shared_ptr<Mesh> brickMesh = std::make_shared<Mesh>();
    brickMesh->AddVertices(vertices, sizeof(vertices) / sizeof(float));
    brickMesh->AddIndices(indices, sizeof(indices) / sizeof(unsigned int));

    brickMesh->SetLayoutBuffer({
        {0, DataType::Float3, "aPos"},
        {1, DataType::Float3, "aNormal"},
        {2, DataType::Float3, "aColor"},
        {3, DataType::Float2, "aTexCoord"}
        });
    brickMesh->Build();
    brickMesh->Bind();

    // brickMaterial->GetShader()->SetBool("material.hasDiffuseMap", true);
    // brickMaterial->GetShader()->SetBool("material.hasSpecularMap", true);
    // brickMaterial->GetShader()->SetBool("material.hasEmissionMap", true);
    // brickMaterial->GetShader()->SetInt("material.diffuseMap", 0);
    // brickMaterial->GetShader()->SetInt("material.specularMap", 1);
    // brickMaterial->GetShader()->SetInt("material.emissionMap", 2);



    // Create light entity
    PointLight* light = new PointLight();
    auto lightMaterial = std::make_shared<Material>(glm::vec3(1.0f, 1.0f, 1.0f),
                                    glm::vec3(1.0f, 0.5f, 0.31f),
                                    glm::vec3(1.0f, 0.5f, 0.31f),
                                    glm::vec3(0.5f, 0.5f, 0.5f),
                                    2.0f,
                                    "resources/white.jpg",
                                    "resources/white.jpg",
                                    "resources/black.jpg");
    auto lightMesh = Mesh::CreateSphere();
    glm::vec3 lightPosition = glm::vec3(0.0f, 1.0f, 3.0f);
    glm::vec3 lightScale = glm::vec3(0.0f, 1.0f, 3.0f);
    lightMaterial->LoadShader("Main Shader","src/render/shaders/light_shader.vert", "src/render/shaders/light_shader.frag");



    bool _applicationRunning = true;
    while (_applicationRunning)
    {
        // _renderer->Update();
        _input->Update();

         // Window* window = CometaRenderer->GetWindow();


        currentCamera->OnUpdate();

        // Bind material
        brickMaterial->Bind();
        brickMesh->Bind();

        brickMaterial->GetShader()->SetMatrix4("uModel",
            Transform::CalculateTransform(
                glm::vec3(0.0, 0.0, -5.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(1.0f, 1.0f, 1.0f)));

        // Bind transformation matricess
        brickMaterial->GetShader()->SetMatrix4("uViewProjection", currentCamera->GetViewProyection());
        brickMaterial->GetShader()->SetFloat3("uViewPos", currentCamera->GetPosition());


        brickMaterial->GetShader()->Bind();
        brickMesh->Bind();
        brickMesh->Draw();

        // light binding
        brickMaterial->GetShader()->SetInt("number_lights", 1);
        std::string light_string = "lights[" + std::to_string(0) + "]";
        brickMaterial->GetShader()->SetFloat3(light_string + ".position", lightPosition);
        brickMaterial->GetShader()->SetFloat3(light_string + ".ambient", light->GetAmbient());
        brickMaterial->GetShader()->SetFloat3(light_string + ".diffuse", light->GetDiffuse());
        brickMaterial->GetShader()->SetFloat3(light_string + ".specular", light->GetSpecular());
        brickMaterial->GetShader()->SetFloat(light_string + ".constant", light->GetConstant());
        brickMaterial->GetShader()->SetFloat(light_string + ".linear", light->GetLinear());
        brickMaterial->GetShader()->SetFloat(light_string + ".quadratic", light->GetQuadratic());

        // glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);

        // render
        _renderer->Render();

        // Define the conditions to close window
        if (Input::IsKeyPressed(GLFW_KEY_ESCAPE) ||
            Renderer::ShouldClose()){ _applicationRunning = false;}
    }


    _input->Close();
    _renderer->Close();
    
    return 0;
}

