//
// Created by Daniel Laplana Gimeno on 18/11/24.
//

#include "core/Application.h"

#include "layer_system/layers/CometaLayer.h"
#include "layer_system/layers/MaterialLayer.h"

Application::Application(){
    this->_isRunning = true;
    _renderer = nullptr; 
    _time = nullptr;
    _onion = Onion();
}

Application::~Application(){

}

void Application::Init(){
    // Create managers
    Time::Create();
    _time = Time::GetInstancePtr();
    
    Renderer::Create();
    _renderer = Renderer::GetInstancePtr();

    Input::Create(); 
    _input = Input::GetInstancePtr();

    // Push the layers
    //CometaLayer* cometaLayer = new CometaLayer();
    //_onion.PushLayer(cometaLayer);
    MaterialLayer* matLayer = new MaterialLayer(); 
    _onion.PushLayer(matLayer); 
    


    // Initialize managers
    _renderer->Init();
    _time->Init();
    _input->Init();

    _onion.Init();
}

void Application::Running() {
    while(this->_isRunning){

        // Update the managers
        _time->Update();
        _renderer->Update();
        _input->Update();

        _onion.Update();
        
        // Check if window must close
        this->_isRunning =  _renderer->_window->ShouldHandleCloseWindow() && !Input::IsKeyPressed(GLFW_KEY_ESCAPE);
    }
}

void Application::Close() {
    _input->Update();
    _renderer->Close();
    _time->Close();

    COMETA_ASSERT("Application closed correctly");
}
