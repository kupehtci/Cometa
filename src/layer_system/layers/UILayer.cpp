//
// Created by Daniel Laplana Gimeno on 1/5/25.
//

#include "UILayer.h"

#include <iostream>
#include <ostream>
#include <layer_system/EventBus.h>
#include <render/Renderer.h>
#include <world/Entity.h>
#include <world/WorldManager.h>
#include <world/Components.h>

#include <filesystem>
#include <string>
#include <vector>
#define GLM_ENABLE_EXPERIMENTAL
#include <input/Input.h>
#include <physics/PhysicsManager.h>
namespace fs = std::filesystem;

// Custom class for UI utilities
#include "ui/UIUtils.h"

#include "core/Application.h"

UILayer::UILayer()
{
    _name = "UILayer";
    // Initialize history arrays with zeros
    for (int i = 0; i < HISTORY_SIZE; i++) {
        _fpsHistory[i] = 0.0f;
        _deltaTimeHistory[i] = 0.0f;
    }
    _historyIndex = 0;
}

UILayer::~UILayer()
{

}

void UILayer::Init()
{
    std::cout << "UILayer::Init" << std::endl;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(Renderer::GetInstancePtr()->GetWindow()->GetGlfwWindow(), true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    // Subscribe to events
    EventBus::GetInstancePtr()->Subscribe(COMETA_KEY_PRESS_EVENT, this);


    ImGuiStyle* style = &ImGui::GetStyle();

    // Fonst assign
    float fontSize = 15.0f;

    io.Fonts->AddFontFromFileTTF("resources/Fonts/jetbrains/JetBrainsMonoNL-Regular.ttf", fontSize);
    io.FontDefault = io.Fonts->AddFontFromFileTTF("resources/Fonts/jetbrains/JetBrainsMonoNL-Regular.ttf", fontSize);

    auto &colors = ImGui::GetStyle().Colors;

    // Windows
    colors[ImGuiCol_WindowBg] = ImVec4{0.1f, 0.1f, 0.13f, 1.0f};
    colors[ImGuiCol_MenuBarBg] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};

    // Border
    colors[ImGuiCol_Border] = ImVec4{0.44f, 0.37f, 0.61f, 0.29f};
    colors[ImGuiCol_BorderShadow] = ImVec4{0.0f, 0.0f, 0.0f, 0.24f};

    // Text
    colors[ImGuiCol_Text] = ImVec4{1.0f, 1.0f, 1.0f, 1.0f};
    colors[ImGuiCol_TextDisabled] = ImVec4{0.5f, 0.5f, 0.5f, 1.0f};

    // Headers
    colors[ImGuiCol_Header] = ImVec4{0.13f, 0.13f, 0.17, 1.0f};
    colors[ImGuiCol_HeaderHovered] = ImVec4{0.19f, 0.2f, 0.25f, 1.0f};
    colors[ImGuiCol_HeaderActive] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};

    // Buttons
    colors[ImGuiCol_Button] = ImVec4{0.13f, 0.13f, 0.17, 1.0f};
    colors[ImGuiCol_ButtonHovered] = ImVec4{0.19f, 0.2f, 0.25f, 1.0f};
    colors[ImGuiCol_ButtonActive] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_CheckMark] = ImVec4{0.74f, 0.58f, 0.98f, 1.0f};

    // Popups
    colors[ImGuiCol_PopupBg] = ImVec4{0.1f, 0.1f, 0.13f, 0.92f};

    // Slider
    colors[ImGuiCol_SliderGrab] = ImVec4{0.44f, 0.37f, 0.61f, 0.54f};
    colors[ImGuiCol_SliderGrabActive] = ImVec4{0.74f, 0.58f, 0.98f, 0.54f};

    // Frame BG
    colors[ImGuiCol_FrameBg] = ImVec4{0.13f, 0.13, 0.17, 1.0f};
    colors[ImGuiCol_FrameBgHovered] = ImVec4{0.19f, 0.2f, 0.25f, 1.0f};
    colors[ImGuiCol_FrameBgActive] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_TabHovered] = ImVec4{0.24, 0.24f, 0.32f, 1.0f};
    colors[ImGuiCol_TabActive] = ImVec4{0.2f, 0.22f, 0.27f, 1.0f};
    colors[ImGuiCol_TabUnfocused] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};

    // Title
    colors[ImGuiCol_TitleBg] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_TitleBgActive] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};

    // Scrollbar
    colors[ImGuiCol_ScrollbarBg] = ImVec4{0.1f, 0.1f, 0.13f, 1.0f};
    colors[ImGuiCol_ScrollbarGrab] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4{0.19f, 0.2f, 0.25f, 1.0f};
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4{0.24f, 0.24f, 0.32f, 1.0f};

    // Seperator
    colors[ImGuiCol_Separator] = ImVec4{0.44f, 0.37f, 0.61f, 1.0f};
    colors[ImGuiCol_SeparatorHovered] = ImVec4{0.74f, 0.58f, 0.98f, 1.0f};
    colors[ImGuiCol_SeparatorActive] = ImVec4{0.84f, 0.58f, 1.0f, 1.0f};

    // Resize Grip
    colors[ImGuiCol_ResizeGrip] = ImVec4{0.44f, 0.37f, 0.61f, 0.29f};
    colors[ImGuiCol_ResizeGripHovered] = ImVec4{0.74f, 0.58f, 0.98f, 0.29f};
    colors[ImGuiCol_ResizeGripActive] = ImVec4{0.84f, 0.58f, 1.0f, 0.29f};

    // Docking
    colors[ImGuiCol_DockingPreview] = ImVec4{0.44f, 0.37f, 0.61f, 1.0f};

    style->TabRounding = 4;
    style->ScrollbarRounding = 9;
    style->WindowRounding = 7;
    style->GrabRounding = 3;
    style->FrameRounding = 3;
    style->PopupRounding = 4;
    style->ChildRounding = 4;
}

void UILayer::Update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    float deltaTime = Time::GetDeltaTime();
    float fps = 1/deltaTime;
    
    // Update plot timer for the Performance Graphs
    _plotUpdateTimer += deltaTime;
    if (_plotUpdateTimer >= 1.0f) {
        _fpsHistory[_historyIndex] = fps;
        _deltaTimeHistory[_historyIndex] = deltaTime;
        _historyIndex = (_historyIndex + 1) % HISTORY_SIZE;
        _plotUpdateTimer = 0.0f;
    }

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_None
    | ImGuiWindowFlags_NoCollapse
    | ImGuiWindowFlags_MenuBar;

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Framed |
                           ImGuiTreeNodeFlags_SpanAvailWidth |
                           ImGuiTreeNodeFlags_FramePadding;

    if (ImGui::Begin("Cometa", &_mainWindowOpen, windowFlags))
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Scene utils"))
            {
                if (ImGui::MenuItem("Show scene hierarchy"))
                {
                    ImGui::Text("Hierarchy");
                    _sceneHierarchyOpen  = !_sceneHierarchyOpen;
                }

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::SeparatorText("Time");
        ImGui::Text("Current DeltaTime %f", deltaTime);
        ImGui::Text("Current FPS %f", fps);
        ImGui::Text("Current Time Scale %f", Time::GetTimeScale());

        // Display FPS and Delta Time graphs
        ImGui::SeparatorText("Performance Graphs");
        
        // Performance Graphs
        // FPS Graph
        ImGui::Text("FPS History (Last 30 seconds, updated every 2 seconds)");
        ImGui::PlotLines("##FPS", _fpsHistory, HISTORY_SIZE, _historyIndex, 
            "FPS", 0.0f, 200.0f, ImVec2(-1, 80.0f));
        
        // Delta Time Graph
        ImGui::Text("Delta Time History (Last 30 seconds, updated every 2 seconds)");
        ImGui::PlotLines("##DeltaTime", _deltaTimeHistory, HISTORY_SIZE, _historyIndex, 
            "Delta Time (s)", 0.0f, 0.1f, ImVec2(-1, 80.0f));

        // end of Performance Graphcs


        ImGui::SeparatorText("Joysticks");

        if (Input::IsJoystickConnected(CometaJoystick::JOYSTICK_1) && Input::IsJoystickAGamepad(JOYSTICK_1)){
            if (ImGui::TreeNode("Joystick 1"))
            {
                CometaGamepadInfo gamepadInfo = Input::GetGamepadInfo(JOYSTICK_1);
                float axa[2] = {gamepadInfo.axes[0], gamepadInfo.axes[1]};
                ImGui::DragFloat2("J1 Axis left", axa);
                float axb[2] = {gamepadInfo.axes[2], gamepadInfo.axes[3]};
                ImGui::DragFloat2("J1 Axis right", axb);

                ImGui::TreePop();
            }
        }

        if (Input::IsJoystickConnected(CometaJoystick::JOYSTICK_2) && Input::IsJoystickAGamepad(JOYSTICK_2)){
            if (ImGui::TreeNode("Joystick 2"))
            {
                CometaGamepadInfo gamepadInfo = Input::GetGamepadInfo(JOYSTICK_2);
                float axa[2] = {gamepadInfo.axes[0], gamepadInfo.axes[1]};
                ImGui::DragFloat2("J2 Axis left", axa);
                float axb[2] = {gamepadInfo.axes[2], gamepadInfo.axes[3]};
                ImGui::DragFloat2("J2 Axis right", axb);

                ImGui::TreePop();
            }
        }

        ImGui::SeparatorText("Physics simulation");

        PhysicsManager* physicsManager = PhysicsManager::GetInstancePtr();

        isOnSimulation = physicsManager->IsOnSimulation();
        if (ImGui::Checkbox("OnSimulation", &isOnSimulation)){
            PhysicsManager::GetInstancePtr()->SetOnSimulation(isOnSimulation);
        }

        float globalGravity[3] = {physicsManager->GetGravity().x, physicsManager->GetGravity().y, physicsManager->GetGravity().z};
        if (ImGui::DragFloat3("Gravity", globalGravity)){
            physicsManager->SetGravity(glm::vec3(globalGravity[0], globalGravity[1], globalGravity[2]));
        }

        float beta = physicsManager->GetBeta();
        if (ImGui::DragFloat("Baumgarte Coefficient", &beta, 0.05, 0.0f, 1.0f)){
            physicsManager->SetBeta(beta);
        }

        ImGui::SeparatorText("Onion layers");
        Onion* onion = Application::GetInstancePtr()->GetOnion();
        uint8_t layerCounter = 0;
        for (auto it = onion->begin(); it != onion->end(); ++it)
        {
            Layer* layer = *it;
            ImGui::Text("%i - %s", layerCounter, layer->GetName().c_str());
            layerCounter++;
        }
        ImGui::Text("Number of layers: %i", layerCounter);
        ImGui::Separator();


        ImGui::End();
    }


    // ------------ SCENE HIERARCHY ------------
    BuildSceneHierarchyPanel();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UILayer::Close()
{
    std::cout << "UILayer::Close" << std::endl;

    // Shutdown imgui's context and backends
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UILayer::HandleEvent(Event& event)
{
    ImGuiIO& io = ImGui::GetIO();

    // If ImGUI doesnt want to capture, dont handle events
    if (!io.WantCaptureKeyboard && !io.WantCaptureMouse){
        return;
    }

    // Handle IMGUI events
    std::cout << "UILayer::HandleEvent" << std::endl;

    // Implement ImGUI event handling here
}


// UI METHODS

void UILayer::BuildSceneHierarchyPanel()
{
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_None
    | ImGuiWindowFlags_NoCollapse
    | ImGuiWindowFlags_MenuBar;

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Framed |
                           ImGuiTreeNodeFlags_SpanAvailWidth |
                           ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_Framed;

    if (_sceneHierarchyOpen && ImGui::Begin("Scene Hierarchy", &_sceneHierarchyOpen, windowFlags))
    {
        // Get the current world from WorldManager
        std::shared_ptr<World> currentWorld = WorldManagerRef->GetCurrentWorld();

        if (currentWorld)
        {
            // Display all entities in the world
            auto& entities = currentWorld->GetEntities();
            for (auto& entity : entities)
            {

                // Create a tree node for each entity
                std::string entityName = entity.GetName();
                if (entityName.empty()) {
                    entityName = "Entity " + std::to_string(entity.GetUID());
                }

                if (ImGui::TreeNodeEx(entityName.c_str(), flags))
                {
                    // Display entity UID
                    ImGui::Text("UID: %u", entity.GetUID());

                    // Display Transform component if it exists
                    Transform* transform = entity.GetComponent<Transform>();
                    if (transform)
                    {
                        if (ImGui::TreeNode("Transform"))
                        {

                            // POSITION
                            float position[3] = { transform->position.x, transform->position.y, transform->position.z };
                            if (ImGui::DragFloat3("Position", position, 0.1f))
                            {
                                transform->position.x = position[0];
                                transform->position.y = position[1];
                                transform->position.z = position[2];
                            }

                            // ROTATION
                            float rotation[3] = { transform->rotation.x, transform->rotation.y, transform->rotation.z };
                            if (ImGui::DragFloat3("Rotation", rotation, 0.1f))
                            {
                                transform->rotation.x = rotation[0];
                                transform->rotation.y = rotation[1];
                                transform->rotation.z = rotation[2];
                            }

                            // SCALE
                            float scale[3] = { transform->scale.x, transform->scale.y, transform->scale.z };
                            if (ImGui::DragFloat3("Scale", scale, 0.05f)) {
                                transform->scale.x = scale[0];
                                transform->scale.y = scale[1];
                                transform->scale.z = scale[2];
                            }

                            ImGui::Text("Parent Transform: ");
                            transform->GetParent() != nullptr ? ImGui::Text("Parent Transform UID: %u", transform->GetParent()->GetOwner()->GetUID()) : ImGui::Text("none");

                            ImGui::TreePop();
                        }
                    }

                    // Display MeshRenderable component if it exists
                    MeshRenderable* meshRenderable = entity.GetComponent<MeshRenderable>();
                    if (meshRenderable)
                    {
                        if (ImGui::TreeNode("MeshRenderable"))
                        {
                            ImGui::Text("Has Material: %s", meshRenderable->GetMaterial() ? "Yes" : "No");
                            ImGui::Text("Has Mesh: %s", meshRenderable->GetMesh() ? "Yes" : "No");
                            ImGui::Dummy(ImVec2(0,10));

                            // Mesh Block
                            if (ImGui::TreeNode("Mesh"))
                            {
                                std::shared_ptr<Mesh> mesh = meshRenderable->GetMesh();
                                if (mesh)
                                {
                                    ImGui::SeparatorText("Mesh properties");
                                    ImGui::Text("Vertices: %d", mesh->GetNumVertices());
                                    ImGui::Text("Indices: %d", mesh->GetNumIndices());
                                    ImGui::Text("VAO ID: %u" , mesh->GetVertexArray()->GetUid());
                                    ImGui::Text("EBO ID: %u" , mesh->GetVertexArray()->GetIndexBuffer()->GetUid());
                                    std::vector<std::shared_ptr<VertexBuffer>> vbos = mesh->GetVertexArray()->GetVertexBuffers();
                                    ImGui::Text("Vertex Buffers: %u", vbos.size());
                                    unsigned int i = 0;
                                    for (auto vbo : vbos)
                                    {
                                        ImGui::Text("\t VBO [%u] UID: %u", i, vbo->GetUid());
                                    }
                                    ImGui::Dummy(ImVec2(0,10));

                                    ImGui::SeparatorText("Layout Buffer");
                                    ImGui::Text("%s", mesh->GetVertexArray()->GetLayoutBuffer().ToString().c_str());
                                    ImGui::Dummy(ImVec2(0,10));

                                    ImGui::TreePop();
                                }
                                else
                                {
                                    ImGui::Text("No mesh");
                                }
                            }

                            // Material Block
                            if (ImGui::TreeNode("Material"))
                            {
                                std::shared_ptr<Material> material = meshRenderable->GetMaterial();
                                if (material)
                                {

                                    // Texture properties
                                    ImGui::SeparatorText("Material properties");

                                    float color[3] = {material->GetColor().x, material->GetColor().y, material->GetColor().z};
                                    if (ImGui::ColorPicker3("", color, ImGuiColorEditFlags_Float )){
                                        material->SetColor(glm::vec3(color[0], color[1], color[2]));
                                    }

                                    float shine = material->GetShininess();
                                    if (ImGui::SliderFloat("Shininess", &shine, 0.0f, 256.0f))
                                    {
                                        material->SetShininess(shine);
                                    }

                                    ImGui::Separator();

                                    // ====== MATERIAL MAPS ======
                                    ImGui::SeparatorText("DIFFUSE MAP");
                                    if(material->GetDiffuseMap())
                                    {
                                        ImGui::Text("Path: %s", material->GetDiffuseMap()->GetPath().c_str());
                                        ImGui::Text("Resolution: %d x %d", material->GetDiffuseMap()->GetWidth(), material->GetDiffuseMap()->GetHeight());
                                        ImGui::Image(material->GetDiffuseMap()->GetUID(), _thumbnailSize);
                                        ImGui::Dummy(ImVec2(0,10));
                                    }
                                    else
                                    {
                                        ImGui::Text("No diffuse map");
                                    }

                                    ImGui::SeparatorText("SPECULAR MAP");
                                    if(material->GetSpecularMap())
                                    {
                                        ImGui::Text("Path: %s", material->GetSpecularMap()->GetPath().c_str());
                                        ImGui::Text("Resolution: %d x %d", material->GetSpecularMap()->GetWidth(), material->GetSpecularMap()->GetHeight());
                                        ImGui::Image(material->GetSpecularMap()->GetUID(), _thumbnailSize);
                                        ImGui::Dummy(ImVec2(0,10));
                                    }
                                    else
                                    {
                                        ImGui::Text("No specular map");
                                    }

                                    ImGui::SeparatorText("EMISSION MAP");
                                    if(material->GetEmissionMap())
                                    {
                                        ImGui::Text("Path: %s", material->GetEmissionMap()->GetPath().c_str());
                                        ImGui::Text("Resolution: %d x %d", material->GetEmissionMap()->GetWidth(), material->GetEmissionMap()->GetHeight());
                                        ImGui::Image(material->GetEmissionMap()->GetUID(), _thumbnailSize);
                                        ImGui::Dummy(ImVec2(0,10));
                                    }

                                    // ====== SHADER ======
                                    std::shared_ptr<Shader> shader = material->GetShader();
                                    if (shader)
                                    {
                                        ImGui::SeparatorText("SHADER");
                                        ImGui::Text("Shader UID: %u", shader->GetShaderUID());

                                        ImGui::Text("Vertex Shader");
                                        // ImGui::TextUnformatted("%s", shader->GetFilePath(GL_VERTEX_SHADER).c_str());
                                        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.3f, 0.0f, 0.3f, 1.0f));
                                        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
                                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                                        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20, 20));

                                        ImGui::BeginChild("Vertex shader source code", ImVec2(0,300), ImGuiChildFlags_Border, ImGuiWindowFlags_HorizontalScrollbar);
                                        ImGui::TextUnformatted(shader->GetSourceCode(GL_VERTEX_SHADER).c_str());
                                        ImGui::EndChild();

                                        ImGui::PopStyleColor(1);
                                        ImGui::Dummy(ImVec2(0,10));
                                        ImGui::Text("Fragment Shader");
                                        ImGui::Dummy(ImVec2(0,10));
                                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

                                        // ImGui::TextUnformatted("%s", shader->GetFilePath(GL_FRAGMENT_SHADER).c_str());
                                        ImGui::BeginChild("Fragment shader source code", ImVec2(0,300), ImGuiChildFlags_Border, ImGuiWindowFlags_HorizontalScrollbar);
                                        ImGui::TextUnformatted(shader->GetSourceCode(GL_FRAGMENT_SHADER).c_str());
                                        ImGui::EndChild();

                                        ImGui::PopStyleColor(3);
                                        ImGui::PopStyleVar(1);
                                    }
                                }
                                else
                                {
                                    ImGui::Text("No material");
                                }

                                ImGui::TreePop();
                            }
                            ImGui::TreePop();
                            ImGui::Separator();
                        }
                    }

                    // Display PointLight component if it exists
                    PointLight* pointLight = entity.GetComponent<PointLight>();
                    if (pointLight)
                    {
                        if (ImGui::TreeNode("PointLight"))
                        {
                            ImGui::SeparatorText("Light properties");

                            // ImGui::Text("Ambient: (%.2f, %.2f, %.2f)",
                            //     pointLight->GetAmbient().x, pointLight->GetAmbient().y, pointLight->GetAmbient().z);
                            float ambientPointLight[3] = {pointLight->GetAmbient().x, pointLight->GetAmbient().y, pointLight->GetAmbient().z};
                            if (ImGui::DragFloat3("Ambient", ambientPointLight, 0.01f)){
                                pointLight->SetAmbient(glm::vec3(ambientPointLight[0], ambientPointLight[1], ambientPointLight[2]));
                            }

                            // ImGui::Text("Diffuse: (%.2f, %.2f, %.2f)",
                            //     pointLight->GetDiffuse().x, pointLight->GetDiffuse().y, pointLight->GetDiffuse().z);
                            float diffusePointLight[3] = {pointLight->GetDiffuse().x, pointLight->GetDiffuse().y, pointLight->GetDiffuse().z};
                            if (ImGui::DragFloat3("Diffuse", diffusePointLight, 0.01f)){
                                pointLight->SetDiffuse(glm::vec3(diffusePointLight[0], diffusePointLight[1], diffusePointLight[2]));
                            }

                            // ImGui::Text("Specular: (%.2f, %.2f, %.2f)",
                            //     pointLight->GetSpecular().x, pointLight->GetSpecular().y, pointLight->GetSpecular().z);
                            float specularPointLight[3] = {pointLight->GetSpecular().x, pointLight->GetSpecular().y, pointLight->GetSpecular().z};
                            if (ImGui::DragFloat3("Specular", specularPointLight, 0.01f)){
                                pointLight->SetSpecular(glm::vec3(specularPointLight[0], specularPointLight[1], specularPointLight[2]));
                            }

                            ImGui::SeparatorText("Attenuation");

                            float constant = pointLight->GetConstant();
                            if (ImGui::DragFloat("Constant", &constant, 0.01f)){
                                pointLight->SetConstant(constant);
                            }

                            float linear = pointLight->GetLinear();
                            if (ImGui::DragFloat("Linear", &linear, 0.01f)){
                                pointLight->SetLinear(linear);
                            }

                            float quadratic = pointLight->GetQuadratic();
                            if (ImGui::DragFloat("Quadratic", &quadratic, 0.01f)){
                                pointLight->SetQuadratic(quadratic);
                            }

                            // Plot graphical representation of the attenuation
                            float att[] = {constant + linear * 1 + quadratic * 1,
                                            constant + linear * 3 + quadratic * 9,
                                            constant + linear * 5 + quadratic * 25,
                                            constant + linear * 10 + quadratic * 100,
                                            constant + linear * 20 + quadratic * 400,
                                            constant + linear * 40 + quadratic * 1600,
                                            constant + linear * 60 + quadratic * 3600};
                            ImGui::PlotLines("Attenuation graph", att, IM_ARRAYSIZE(att));

                            ImGui::TreePop();

                            ImGui::Separator();
                        }
                    }

                    // Display DirectionalLight component if it exists
                    DirectionalLight* dirLight = entity.GetComponent<DirectionalLight>();
                    if (dirLight)
                    {
                        if (ImGui::TreeNode("DirectionalLight"))
                        {
                            // Directional Light direction
                            float direction[3] = {dirLight->GetDirection().x, dirLight->GetDirection().y , dirLight->GetDirection().z };
                            if (ImGui::DragFloat3("Direction", direction, 0.1f)) {
                                dirLight->SetDirection(glm::vec3(direction[0], direction[1], direction[2]));
                            }

                            // Directional Light ambient
                            float ambientDirLight[3] = { dirLight->GetAmbient().x, dirLight->GetAmbient().y, dirLight->GetAmbient().z};
                            if (ImGui::DragFloat3("Ambient", ambientDirLight, 0.01f, 0.0f, 1.0f)) {
                                dirLight->SetAmbient(glm::vec3(ambientDirLight[0], ambientDirLight[1], ambientDirLight[2]));
                            }

                            // Directional Light diffuse
                            float diffuseDirLight[3] = { dirLight->GetDiffuse().x, dirLight->GetDiffuse().y, dirLight->GetDiffuse().z };
                            if (ImGui::DragFloat3("Diffuse", diffuseDirLight, 0.01f, 0.0f, 1.0f)) {
                                dirLight->SetDiffuse(glm::vec3(diffuseDirLight[0], diffuseDirLight[1], diffuseDirLight[2]));
                            }

                            float specularDirLight[3] =  {dirLight->GetSpecular().x, dirLight->GetSpecular().y, dirLight->GetSpecular().z};
                            if (ImGui::DragFloat3("Specular", specularDirLight, 0.1f, 0.0f, 1.0f)){
                                dirLight->SetSpecular(glm::vec3(specularDirLight[0], specularDirLight[1], specularDirLight[2]));
                            }

                            ImGui::TreePop();

                            ImGui::Separator();
                        }
                    }

                    // Display Tag component if it exists
                    Tag* tag = entity.GetComponent<Tag>();
                    if (tag)
                    {
                        if (ImGui::TreeNode("Tag"))
                        {
                            ImGui::Text("Tag: %s", tag->GetTag().c_str());
                            ImGui::TreePop();

                            ImGui::Separator();
                        }
                    }

                    // Display Collider component if it exists
                    ColliderComponent* colliderComp = entity.GetComponent<ColliderComponent>();
                    if (colliderComp)
                    {
                        if (ImGui::TreeNode("Collider"))
                        {
                            ImGui::Text("Collider Component");

                            Collider* collider = colliderComp->GetCollider();
                            if (collider != nullptr)
                            {
                                if (dynamic_cast<BoxCollider*>(collider) != nullptr)
                                {
                                    ImGui::Text("---Box Collider---");
                                    BoxCollider* boxCollider = dynamic_cast<BoxCollider*>(collider);

                                    float boxColliderExtents[3] = {boxCollider->GetExtents().x, boxCollider->GetExtents().y, boxCollider->GetExtents().z};
                                    if (ImGui::DragFloat3("Extents", boxColliderExtents, 0.01f, 0.0f, 0))
                                    {
                                        boxCollider->SetExtents(glm::vec3(boxColliderExtents[0], boxColliderExtents[1], boxColliderExtents[2]));
                                    }

                                    float boxColliderCenterOffset[3] = {boxCollider->GetCenter().x, boxCollider->GetCenter().y, boxCollider->GetCenter().z };
                                    if (ImGui::DragFloat3("Center", boxColliderCenterOffset, 0.1f, 0.0f, 0))
                                    {
                                        boxCollider->SetCenter(glm::vec3(boxColliderCenterOffset[0], boxColliderCenterOffset[1], boxColliderCenterOffset[2]));
                                    }

                                    float boxColliderRotation[4] = { boxCollider->GetRotation().w, boxCollider->GetRotation().x, boxCollider->GetRotation().y, boxCollider->GetRotation().z};
                                    if (ImGui::DragFloat4( "Rotation (w, x, y, z)", boxColliderRotation, 0.01f, 0.0f, 1.0f))
                                    {
                                        boxCollider->SetRotation(glm::quat(boxColliderRotation[0], boxColliderRotation[1], boxColliderRotation[2], boxColliderRotation[3]));
                                    }

                                }
                                else if (dynamic_cast<SphereCollider*>(collider) != nullptr)
                                {
                                    ImGui::Text("---Sphere Collider---");
                                    SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider);

                                    float sphereColliderCenterOffset[3] = {sphereCollider->GetCenter().x, sphereCollider->GetCenter().y, sphereCollider->GetCenter().z };
                                    if (ImGui::DragFloat3("Center", sphereColliderCenterOffset, 0.1f, 0.0f, 0))
                                    {
                                        sphereCollider->SetCenter(glm::vec3(sphereColliderCenterOffset[0], sphereColliderCenterOffset[1], sphereColliderCenterOffset[2]));
                                    }

                                    float sphereRadius = sphereCollider->GetRadius();
                                    if (ImGui::SliderFloat("Radius", &sphereRadius, 0.01f, 0.0f, "%.2f"))
                                    {
                                        sphereCollider->SetRadius(sphereRadius);
                                    }
                                }
                            }
                            else
                            {
                                ImGui::Text("Not defined Collider in Collider Component");
                            }

                            ImGui::TreePop();
                            ImGui::Separator();
                        }
                    }

                    // Display RigidBody component if it exists
                    RigidBody* rigidBody = entity.GetComponent<RigidBody>();
                    if (rigidBody)
                    {
                        if (ImGui::TreeNode("RigidBody"))
                        {
                            if (ImGui::Checkbox("Enabled", &rigidBody->GetEnabledRef()))

                            if (ImGui::SmallButton("Reset")) {
                                rigidBody->Reset();
                            }

                            bool isAffectedGravity = rigidBody->IsAffectedByGravity();
                            if (ImGui::Checkbox("Affected by gravity", &isAffectedGravity))
                            {
                                rigidBody->SetAffectedByGravity(isAffectedGravity);
                            }

                            ImGui::Text("Linear movement");

                            float mass = rigidBody->GetMass();
                            if (ImGui::DragFloat("Mass", &mass, 0.01f, 0.0f, 1.0f))
                            {
                                rigidBody->SetMass(mass);
                            }

                            float linVel[3] = {rigidBody->GetLinearVelocity().x, rigidBody->GetLinearVelocity().y, rigidBody->GetLinearVelocity().z};
                            if (ImGui::DragFloat3("Linear Velocity", linVel, 0.01f)){
                                rigidBody->SetLinearVelocity({linVel[0], linVel[1], linVel[2]});
                            }

                            float force[3] = {rigidBody->GetForce().x, rigidBody->GetForce().y, rigidBody->GetForce().z};
                            if (ImGui::DragFloat3("Force ", force, 0.01f, 0.0f, 1.0f))
                            {
                                rigidBody->SetForce({force[0], force[1], force[2]});
                            }

                            ImGui::Text("Angular movement");
                            float torque[3] = {rigidBody->GetTorque().x, rigidBody->GetTorque().y, rigidBody->GetTorque().z};
                            if (ImGui::DragFloat3("Torque ", torque, 0.01f, 0.0f, 1.0f))
                            {
                                rigidBody->SetTorque({torque[0], torque[1], torque[2]});
                            }

                            float angularVel[3] = {rigidBody->GetAngularVelocity().x, rigidBody->GetAngularVelocity().y, rigidBody->GetAngularVelocity().z};
                            if (ImGui::DragFloat3("Angular velocity", angularVel, 0.01f, 0.0f, 1.0))
                            {
                                rigidBody->SetAngularVelocity(glm::vec3(angularVel[0], angularVel[1], angularVel[2]));
                            }

                            CometaUIUtils::ShowMat3(rigidBody->GetInertiaTensor(), "Inertia tensor", true);
                            CometaUIUtils::ShowMat3(rigidBody->GetInverseInertiaTensor(), "Inverse Inertia tensor", true);

                            ImGui::TreePop();
                        }
                    }
                    
                    // Display Script component if it exists
                    Script* script = entity.GetComponent<Script>();
                    if (script)
                    {
                        if (ImGui::TreeNode("Script"))
                        {
                            ImGui::TreePop();
                        }
                    }

                    ImGui::TreePop();
                }
                ImGui::Separator();

            }
        }
        else
        {
            ImGui::Text("No active world");
        }

        ImGui::End();
    }
}
