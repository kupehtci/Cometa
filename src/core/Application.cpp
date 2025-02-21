//
// Created by Daniel Laplana Gimeno on 18/11/24.
//

#include "core/Application.h"
#include "../input/Input.h"

Application::Application(){
    this->_isRunning = true;
    _renderer = nullptr; 
    _time = nullptr; 
}

Application::~Application(){

}

void Application::Init(){
    // Create managers
    Time::Create();
    _time = Time::GetInstancePtr();
    
    Renderer::Create();
    _renderer = Renderer::GetInstancePtr();

    

    // Initialize managers
    _renderer->Init();

    _time->Init(); 
}

void Application::Running() {
    while(this->_isRunning){

        // Update the managers
        _time->Update(); 

        _renderer->Update();
        
        // Check if window must close
        this->_isRunning =  _renderer->_window->ShouldHandleCloseWindow() && !Input::IsKeyPressed(GLFW_KEY_ESCAPE);
    }
}

void Application::Close() {
    _renderer->Close();

    COMETA_ASSERT("Application closed correctly");
}
