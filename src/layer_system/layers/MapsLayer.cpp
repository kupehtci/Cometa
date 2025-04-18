//
// Created by Daniel Laplana Gimeno on 18/4/25.
//

#include "MapsLayer.h"

#include "render/Renderer.h"
#include "render/Shader.h"


MapsLayer::MapsLayer()
{

}

MapsLayer::~MapsLayer()
{

}

void MapsLayer::Init()
{
    std::cout << "Maps layer init" << std::endl;

    _texture = new Texture("./resources/macos_example.jpg");
    _camera = Camera();

    _mat = Material(glm::vec3(1.0f, 1.0f, 1.0f),
                                    glm::vec3(1.0f, 0.5f, 0.31f),
                                    glm::vec3(1.0f, 0.5f, 0.31f),
                                    glm::vec3(0.5f, 0.5f, 0.5f),
                                    2.0f,
                                    "resources/bricks_diffuse_map.jpg",
                                    "resources/bricks_specular_map.jpg");
}

void MapsLayer::Update()
{
    Shader* mainShader = new Shader("Main Shader", "src/render/shaders/light_map_shader.vert", "src/render/shaders/light_map_shader.frag");
    mainShader->Bind();

    Texture* materialDiffuseMap = _mat.GetDiffuseMap();
    int diffuseMapIndex = 0;
    mainShader->SetInt("material.diffuse", diffuseMapIndex);
    materialDiffuseMap->Bind(diffuseMapIndex);


    Texture* materialSpecularMap = _mat.GetSpecularMap();
    int specularMapIndex = 1;
    mainShader->SetInt("material.specular", specularMapIndex);
    materialSpecularMap->Bind(specularMapIndex);

    mainShader->SetFloat3("material.color", _mat.GetColor());
    // mainShader->SetFloat3("material.ambient", mat.GetAmbient());
    mainShader->SetFloat3("material.diffuse", _mat.GetDiffuse());
    mainShader->SetFloat3("material.specular", _mat.GetSpecular());
    mainShader->SetFloat("material.shininess", _mat.GetShininess());

    glm::vec3 lightPosition = glm::vec3(glm::cos(glfwGetTime()), glm::cos(glfwGetTime()) , -2.0f);

    mainShader->SetFloat3("light.position", lightPosition);
    mainShader->SetFloat3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f)/*glm::vec3(0.2f, 0.2f, 0.2f)*/);
    mainShader->SetFloat3("light.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
    mainShader->SetFloat3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

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




    VertexArray vArray0 = VertexArray();
    vArray0.Bind();

    VertexBuffer vBuffer0 = VertexBuffer(vertices, sizeof(vertices));
    IndexBuffer iBuffer0 = IndexBuffer(indices, sizeof(indices));


    LayoutBuffer layoutBuffer = {
            {0, DataType::Float3, "aPos"},
            {1, DataType::Float3, "aNormal"},
            {2, DataType::Float3, "aColor"},
            {3, DataType::Float2, "aTexCoord"}
    };

    layoutBuffer.Build();
    layoutBuffer.Bind();

    // Update camera and its proyection
    _camera.OnUpdate();
    mainShader->SetMatrix4("uViewProjection", _camera.GetViewProyection());
    mainShader->SetFloat3("viewPos", _camera.GetPosition());                    // Set the view position for the fragment shader


    glm::mat4 modelRotated = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    mainShader->SetMatrix4("uModel", modelRotated);

    vArray0.Bind();


    mainShader->Bind();
    // materialDiffuseMap->Bind(0);

    vArray0.Bind();

    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);

    mainShader->Unbind();


    // --------- Draw LIGHT POINT ---------

    Shader* lightShader = new Shader("Light Shader", "src/render/shaders/light_shader.vert", "src/render/shaders/light_shader.frag");
    lightShader->Bind();

    lightShader->SetMatrix4("uViewProjection", _camera.GetViewProyection());
    glm::mat4 lightPosMatrix = glm::translate(glm::mat4(1.0f), lightPosition);
    lightPosMatrix = glm::scale(lightPosMatrix, glm::vec3(0.2f, 0.2f, 0.2f));

    lightShader->SetMatrix4("uModel", lightPosMatrix);

    vArray0.Bind();

    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);

    lightShader->Unbind();

    // --------- END OF DRAWING LIGHT POINT ---------



    //
    // // REPETITION
    //
    // Shader* mainShader1 = new Shader("Main Shader", "src/render/shaders/light_map_shader.vert", "src/render/shaders/light_map_shader.frag");
    // mainShader1->Bind();
    //
    // Texture* materialDiffuseMap1 = _mat.GetSpecularMap();
    // int diffuseMapIndex1 = 0;
    // mainShader1->SetInt("material.diffuse", diffuseMapIndex1);
    //
    // mainShader1->SetFloat3("material.color", _mat.GetColor());
    //
    // mainShader1->SetFloat3("material.diffuse", _mat.GetDiffuse());
    // mainShader1->SetFloat3("material.specular", _mat.GetSpecular());
    // mainShader1->SetFloat("material.shininess", _mat.GetShininess());
    //
    // glm::vec3 lightPosition1 = glm::vec3(glm::cos(glfwGetTime()), 5.0f , -2.0f);
    //
    // mainShader1->SetFloat3("light.position", lightPosition1);
    // mainShader1->SetFloat3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f)/*glm::vec3(0.2f, 0.2f, 0.2f)*/);
    // mainShader1->SetFloat3("light.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
    // mainShader1->SetFloat3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    //
    // float vertices1[] = {
    //     // Front face
    //     // positions          // normals           // colors            // texture coords
    //     -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
    //     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
    //     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
    //     -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    //
    //     // Back face
    //     -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
    //     -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
    //     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
    //     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
    //
    //     // Top face
    //     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
    //     -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
    //     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
    //     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
    //
    //     // Bottom face
    //     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
    //     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
    //     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f,
    //     -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f,
    //
    //     // Right face
    //     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
    //     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,  1.0f, 1.0f,
    //     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
    //     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,  0.0f, 0.0f,
    //
    //     // Left face
    //     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f,
    //     -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 1.0f,  1.0f, 0.0f,
    //     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
    //     -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 1.0f,  0.0f, 1.0f
    // };
    //
    // unsigned int indices1[] = {
    //     0,  1,  2,    2,  3,  0,   // Front
    //     4,  5,  6,    6,  7,  4,   // Back
    //     8,  9,  10,   10, 11, 8,   // Top
    //     12, 13, 14,   14, 15, 12,  // Bottom
    //     16, 17, 18,   18, 19, 16,  // Right
    //     20, 21, 22,   22, 23, 20   // Left
    // };
    //
    //
    //
    //
    // VertexArray vArray1 = VertexArray();
    // vArray1.Bind();
    //
    // VertexBuffer vBuffer1 = VertexBuffer(vertices1, sizeof(vertices1));
    // IndexBuffer iBuffer1 = IndexBuffer(indices1, sizeof(indices1));
    //
    //
    // LayoutBuffer layoutBuffer1 = {
    //         {0, DataType::Float3, "aPos"},
    //         {1, DataType::Float3, "aNormal"},
    //         {2, DataType::Float3, "aColor"},
    //         {3, DataType::Float2, "aTexCoord"}
    // };
    //
    // layoutBuffer1.Build();
    // layoutBuffer1.Bind();
    //
    // // Update camera and its proyection
    // _camera.OnUpdate();
    // mainShader1->SetMatrix4("uViewProjection", _camera.GetViewProyection());
    // mainShader1->SetFloat3("viewPos", _camera.GetPosition());                    // Set the view position for the fragment shader
    //
    //
    // glm::mat4 modelRotated1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 3.0f, -3.0f));
    // mainShader1->SetMatrix4("uModel", modelRotated1);
    //
    // vArray1.Bind();
    //
    //
    // mainShader1->Bind();
    // materialDiffuseMap1->Bind(0);
    //
    // vArray1.Bind();
    //
    // glDrawElements(GL_TRIANGLES, sizeof(indices1) / sizeof(indices1[0]), GL_UNSIGNED_INT, 0);
    //
    // mainShader->Unbind();
    //
    //
    // // --------- Draw LIGHT POINT ---------
    //
    // Shader* lightShader1 = new Shader("Light Shader", "src/render/shaders/light_shader.vert", "src/render/shaders/light_shader.frag");
    // lightShader1->Bind();
    //
    // lightShader1->SetMatrix4("uViewProjection", _camera.GetViewProyection());
    // glm::mat4 lightPosMatrix1 = glm::translate(glm::mat4(1.0f), lightPosition1);
    // lightPosMatrix1 = glm::scale(lightPosMatrix1, glm::vec3(0.2f, 0.2f, 0.2f));
    //
    // lightShader1->SetMatrix4("uModel", lightPosMatrix1);
    //
    // vArray1.Bind();
    //
    // glDrawElements(GL_TRIANGLES, sizeof(indices1) / sizeof(indices1[0]), GL_UNSIGNED_INT, 0);
    //
    // lightShader1->Unbind();
    //
    // // --------- END OF DRAWING LIGHT POINT ---------
}


void MapsLayer::Close()
{

}

void MapsLayer::HandleEvent(Event& event){

}