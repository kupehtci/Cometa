#include "core/Application.h"

#include <layer_system/layers/DemoLayer.h>

#include "layer_system/layers/MapsLayer.h"
#include "layer_system/layers/UILayer.h"
#include "layer_system/layers/DemoLayer.h"

Application::Application(){
    this->_isRunning = true;
    _worldManager = nullptr;
    _physicsManager = nullptr;
    _renderer = nullptr; 
    _time = nullptr;
    _onion = Onion();
}

Application::~Application(){
    delete _worldManager;
    delete _physicsManager;
    delete _renderer;
    delete _time;
}

void Application::Init(){
    Time::Create();
    _time = Time::GetInstancePtr();

    WorldManager::Create();
    _worldManager = WorldManager::GetInstancePtr();

    Renderer::Create();
    _renderer = Renderer::GetInstancePtr();

    Input::Create(); 
    _input = Input::GetInstancePtr();

    PhysicsManager::Create();
    _physicsManager = PhysicsManager::GetInstancePtr();

    // Push the layers
    UILayer* uiLayer = new UILayer();
    _onion.PushLayer(uiLayer);

    DemoLayer* demoLayer = new DemoLayer();
    _onion.PushLayer(demoLayer);

    // Initialize scritpt manager
    ScriptManager::Create();
    _scriptManager = ScriptManager::GetInstancePtr();


    // Initialize managers
    _worldManager->Init();
    _renderer->Init();
    _time->Init();
    _input->Init();
    _physicsManager->Init();
    _onion.Init();

    _scriptManager->Init();
}

void Application::Running() {
    while(_isRunning){

        // Update the managers
        _time->Update();
        _worldManager->Update();
        _physicsManager->Update();
        _renderer->Update();
        _input->Update();
        _onion.Update();
        _scriptManager->Update();


        _renderer->Render();

        // Check if application should close
        if (_isRunning)
        {
            _isRunning = !_renderer->GetWindow()->ShouldHandleCloseWindow();
        }
    }
}

void Application::Close() {
    _scriptManager->Close();
    _physicsManager->Close();
    _input->Close();
    _renderer->Close();
    _worldManager->Close();
    _time->Close();

    COMETA_ASSERT("Application closed correctly");
}
