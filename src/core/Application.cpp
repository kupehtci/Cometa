//
// Created by Daniel Laplana Gimeno on 18/11/24.
//

#include "core/Application.h"


Application::Application(){
    this->_isRunning = true;
}

Application::~Application(){

}

void Application::Init(){
    // Create managers
    Renderer::Create();

    _renderer = Renderer::GetInstancePtr();

    // Initialize managers
    _renderer->Init();


}

void Application::Running() {
    while(this->_isRunning){

        // Update the managers
        _renderer->Update();

        // Check if window must close
        this->_isRunning =  !glfwWindowShouldClose(_renderer->_window);
    }
}

void Application::Close() {
    _renderer->Close();
}
