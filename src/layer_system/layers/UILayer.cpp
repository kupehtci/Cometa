//
// Created by Daniel Laplana Gimeno on 1/5/25.
//

#include "UILayer.h"

#include <iostream>
#include <ostream>
#include <layer_system/EventBus.h>
#include <render/Renderer.h>
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

}

void UILayer::Update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();



    // Update demo window
    ImGui::ShowDemoWindow();

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_None;
    windowFlags |= ImGuiWindowFlags_NoCollapse;

    bool windowOpen = true;

    // if (ImGui::Begin("Cometa", &windowOpen, windowFlags)){
    //     ImGui::Text("UI Layer called this");
    //
    //     // for (auto ent : WorldManager::GetInstancePtr()->)
    //     ImGui::End();
    // }


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
