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


UILayer::UILayer()
{
    _name = "UILayer";
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

    style->WindowPadding = ImVec2(15, 15);
    style->WindowRounding = 5.0f;
    style->FramePadding = ImVec2(5, 5);
    style->FrameRounding = 4.0f;
    style->ItemSpacing = ImVec2(12, 8);
    style->ItemInnerSpacing = ImVec2(8, 6);
    style->IndentSpacing = 25.0f;
    style->ScrollbarSize = 15.0f;
    style->ScrollbarRounding = 9.0f;
    style->GrabMinSize = 5.0f;
    style->GrabRounding = 3.0f;

    //style->ChildRounding = 3.0f; 
    //style->ChildBorderSize = 15.0f;



    style->Colors[ImGuiCol_Text] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.39f, 0.38f, 0.77f);
    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.92f, 0.91f, 0.88f, 0.70f);
    // style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(1.00f, 0.98f, 0.95f, 0.58f);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(0.92f, 0.91f, 0.88f, 0.92f);
    style->Colors[ImGuiCol_Border] = ImVec4(0.84f, 0.83f, 0.80f, 0.65f);
    style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    style->Colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.99f, 1.00f, 0.40f, 0.78f);
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TitleBg] = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_MenuBarBg] = ImVec4(1.00f, 0.98f, 0.95f, 0.47f);
    style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 0.00f, 0.00f, 0.21f);
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.90f, 0.91f, 0.00f, 0.78f);
    style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    // style->Colors[ImGuiCol_ComboBg] = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
    style->Colors[ImGuiCol_CheckMark] = ImVec4(0.25f, 1.00f, 0.00f, 0.80f);
    
    style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.00f, 0.00f, 0.14f);
    style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);

    style->Colors[ImGuiCol_Button] = ImVec4(0.00f, 0.00f, 0.00f, 0.14f);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.99f, 1.00f, 0.22f, 0.86f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);

    style->Colors[ImGuiCol_Header] = ImVec4(0.655f, 0.627f, 0.741f, 0.76f);
    style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.655f, 0.627f, 0.741f, 0.86f);
    style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.655f, 0.627f, 0.741f, 1.00f);

    // style->Colors[ImGuiCol_Column] = ImVec4(0.00f, 0.00f, 0.00f, 0.32f);
    /*style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.25f, 1.00f, 0.00f, 0.78f);
    style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);*/
    style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.04f);
    style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.25f, 1.00f, 0.00f, 0.78f);
    style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
   /* style->Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
    style->Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
    style->Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);*/
    style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
    //style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);

    //// Set ImGUI theme
    //ImVec4* colors = ImGui::GetStyle().Colors;
    //colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    //colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    //colors[ImGuiCol_WindowBg]               = ImVec4(0.04f, 0.04f, 0.04f, 0.94f);
    //colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    //colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    //colors[ImGuiCol_Border]                 = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    //colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    //colors[ImGuiCol_FrameBg]                = ImVec4(0.15f, 0.15f, 0.15f, 0.54f);
    //colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.48f, 0.26f, 0.98f, 0.40f);
    //colors[ImGuiCol_FrameBgActive]          = ImVec4(0.37f, 0.00f, 1.00f, 1.00f);
    //colors[ImGuiCol_TitleBg]                = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    //colors[ImGuiCol_TitleBgActive]          = ImVec4(0.21f, 0.16f, 0.48f, 1.00f);
    //colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    //colors[ImGuiCol_MenuBarBg]              = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    //colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    //colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    //colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    //colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    //colors[ImGuiCol_CheckMark]              = ImVec4(0.45f, 0.26f, 0.98f, 1.00f);
    //colors[ImGuiCol_SliderGrab]             = ImVec4(0.41f, 0.00f, 1.00f, 0.40f);
    //colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.48f, 0.26f, 0.98f, 0.52f);
    //colors[ImGuiCol_Button]                 = ImVec4(0.20f, 0.20f, 0.20f, 0.40f);
    //colors[ImGuiCol_ButtonHovered]          = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
    //colors[ImGuiCol_ButtonActive]           = ImVec4(0.34f, 0.06f, 0.98f, 1.00f);
    //colors[ImGuiCol_Header]                 = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
    //colors[ImGuiCol_HeaderHovered]          = ImVec4(0.15f, 0.15f, 0.15f, 0.80f);
    //colors[ImGuiCol_HeaderActive]           = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
    //colors[ImGuiCol_Separator]              = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    //colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
    //colors[ImGuiCol_SeparatorActive]        = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
    //colors[ImGuiCol_ResizeGrip]             = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
    //colors[ImGuiCol_ResizeGripHovered]      = ImVec4(1.00f, 1.00f, 1.00f, 0.13f);
    //colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    //colors[ImGuiCol_TabHovered]             = ImVec4(0.40f, 0.26f, 0.98f, 0.50f);
    //colors[ImGuiCol_Tab]                    = ImVec4(0.18f, 0.20f, 0.58f, 0.73f);
    //colors[ImGuiCol_TabSelected]            = ImVec4(0.29f, 0.20f, 0.68f, 1.00f);
    //colors[ImGuiCol_TabSelectedOverline]    = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    //colors[ImGuiCol_TabDimmed]              = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
    //colors[ImGuiCol_TabDimmedSelected]      = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
    //colors[ImGuiCol_TabDimmedSelectedOverline]  = ImVec4(0.50f, 0.50f, 0.50f, 0.00f);
    //colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    //colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    //colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    //colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    //colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
    //colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
    //colors[ImGuiCol_TableBorderLight]       = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
    //colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    //colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    //colors[ImGuiCol_TextLink]               = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    //colors[ImGuiCol_TextSelectedBg]         = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
    //colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    //colors[ImGuiCol_NavCursor]              = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    //colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    //colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    //colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

void UILayer::Update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();



    // Update demo window
    // ImGui::ShowDemoWindow();

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_None;
    windowFlags |= ImGuiWindowFlags_NoCollapse;
    //windowFlags |= ImGuiConfigFlags_DockingEnable;

    bool windowOpen = true;

    if (ImGui::Begin("Cometa", &windowOpen, windowFlags)){
        // ImGui::BeginChild("Entities");


    if (ImGui::CollapsingHeader("Scene Hierarchy"))
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

                if (ImGui::TreeNode(entityName.c_str()))
                {
                    // Display entity UID
                    ImGui::Text("UID: %u", entity.GetUID());

                    // Display Transform component if it exists
                    Transform* transform = entity.GetComponent<Transform>();
                    if (transform)
                    {
                        if (ImGui::TreeNode("Transform"))
                        {
                            // ImGui::Text("Position: (%.2f, %.2f, %.2f)",
                            //     transform->position.x, transform->position.y, transform->position.z);

                            float position[3] = { transform->position.x, transform->position.y, transform->position.z };
                            if (ImGui::DragFloat3("Position", position, 0.1f))
                            {
                                transform->position.x = position[0];
                                transform->position.y = position[1];
                                transform->position.z = position[2];
                            }

                            // ImGui::Text("Rotation: (%.2f, %.2f, %.2f)",
                            //     transform->rotation.x, transform->rotation.y, transform->rotation.z);
                            float rotation[3] = { transform->rotation.x, transform->rotation.y, transform->rotation.z };
                            if (ImGui::DragFloat3("Rotation", rotation, 0.1f))
                            {
                                transform->rotation.x = rotation[0];
                                transform->rotation.y = rotation[1];
                                transform->rotation.z = rotation[2];
                            }

                            //ImGui::Text("Scale: (%.2f, %.2f, %.2f)",
                            //    transform->scale.x, transform->scale.y, transform->scale.z);
                            float scale[3] = { transform->scale.x, transform->scale.y, transform->scale.z }; 
                            if (ImGui::DragFloat3("Scale", scale, 0.05f)) {
                                transform->scale.x = scale[0];
                                transform->scale.y = scale[1];
                                transform->scale.z = scale[2];

                            }

                            ImGui::TreePop();
                        }
                    }

                    // Display MeshRenderable component if it exists
                    MeshRenderable* meshRenderable = entity.GetComponent<MeshRenderable>();
                    if (meshRenderable)
                    {
                        if (ImGui::TreeNode("MeshRenderable"))
                        {
                            ImGui::Text("Has Mesh: %s", meshRenderable->GetMesh() ? "Yes" : "No");
                            ImGui::Text("Has Material: %s", meshRenderable->GetMaterial() ? "Yes" : "No");
                            ImGui::TreePop();
                        }
                    }

                    // Display PointLight component if it exists
                    PointLight* pointLight = entity.GetComponent<PointLight>();
                    if (pointLight)
                    {
                        if (ImGui::TreeNode("PointLight"))
                        {
                            ImGui::Text("Ambient: (%.2f, %.2f, %.2f)",
                                pointLight->GetAmbient().x, pointLight->GetAmbient().y, pointLight->GetAmbient().z);
                            ImGui::Text("Diffuse: (%.2f, %.2f, %.2f)",
                                pointLight->GetDiffuse().x, pointLight->GetDiffuse().y, pointLight->GetDiffuse().z);
                            ImGui::Text("Specular: (%.2f, %.2f, %.2f)",
                                pointLight->GetSpecular().x, pointLight->GetSpecular().y, pointLight->GetSpecular().z);
                            ImGui::TreePop();
                        }
                    }

                    // Display DirectionalLight component if it exists
                    DirectionalLight* dirLight = entity.GetComponent<DirectionalLight>();
                    if (dirLight)
                    {
                        if (ImGui::TreeNode("DirectionalLight"))
                        {
                            //ImGui::Text("Direction: (%.2f, %.2f, %.2f)",
                                //dirLight->GetDirection().x, dirLight->GetDirection().y, dirLight->GetDirection().z);

                            float direction[3] = {dirLight->GetDirection().x, dirLight->GetDirection().y , dirLight->GetDirection().z };
                            if (ImGui::DragFloat3("Direction", direction, 0.1f)) {
                                dirLight->SetDirection(glm::vec3(direction[0], direction[1], direction[2])); 
                            }

                            //ImGui::Text("Ambient: (%.2f, %.2f, %.2f)",
                                //dirLight->GetAmbient().x, dirLight->GetAmbient().y, dirLight->GetAmbient().z);

                            float ambientDirLight[3] = { dirLight->GetAmbient().x, dirLight->GetAmbient().y, dirLight->GetAmbient().z};
                            if (ImGui::DragFloat3("Ambient", ambientDirLight, 0.01f, 0.0f, 1.0f)) {
                                dirLight->SetAmbient(glm::vec3(ambientDirLight[0], ambientDirLight[1], ambientDirLight[2]));
                            }

                            //ImGui::Text("Diffuse: (%.2f, %.2f, %.2f)",
                                //dirLight->GetDiffuse().x, dirLight->GetDiffuse().y, dirLight->GetDiffuse().z);

                            float diffuseDirLight[3] = { dirLight->GetDiffuse().x, dirLight->GetDiffuse().y, dirLight->GetDiffuse().z };
                            if (ImGui::DragFloat3("Diffuse", diffuseDirLight, 0.01f, 0.0f, 1.0f)) {
                                dirLight->SetDiffuse(glm::vec3(diffuseDirLight[0], diffuseDirLight[1], diffuseDirLight[2]));
                            }

                            ImGui::TreePop();
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
                        }
                    }

                    // Display Collider component if it exists
                    Collider* collider = entity.GetComponent<Collider>();
                    if (collider)
                    {
                        if (ImGui::TreeNode("Collider"))
                        {
                            ImGui::Text("Collider Component");
                            ImGui::TreePop();
                        }
                    }

                    // Display RigidBody component if it exists
                    RigidBody* rigidBody = entity.GetComponent<RigidBody>();
                    if (rigidBody)
                    {
                        if (ImGui::TreeNode("RigidBody"))
                        {
                            ImGui::Text("Linear Velocity: (%.2f, %.2f, %.2f)",
                                rigidBody->linearVelocity.x, rigidBody->linearVelocity.y, rigidBody->linearVelocity.z);
                            ImGui::Text("Angular Velocity: (%.2f, %.2f, %.2f)",
                                rigidBody->angularVelocity.x, rigidBody->angularVelocity.y, rigidBody->angularVelocity.z);
                            ImGui::Text("Mass: %.2f", rigidBody->mass);
                            ImGui::TreePop();
                        }
                    }

                    ImGui::TreePop();
                }
            }
        }
        else
        {
            ImGui::Text("No active world");
        }
    }


        ImGui::End();
    }


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
}
