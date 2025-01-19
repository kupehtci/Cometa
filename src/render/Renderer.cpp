//
// Created by Daniel Laplana Gimeno on 5/12/24.
//

#include "Renderer.h"
#include "../debug/Assertion.h"
#include <GLFW/glfw3.h>

Renderer::Renderer() {
    // this->_window = nullptr;
    // this->_resolution = new Quad(800, 600);
}

/**
 * Renderer destructor
 */
Renderer::~Renderer() {

}

/**
 * Initialize the Renderer
 */
void Renderer::Init(){

    // Initialize GLFW
    if(!glfwInit()){
        Assertion::Error("Cannot initialize GLFW, review GLFW installation");
        return;
    }

    // Create a Window (Own object)
    // _window = new Window();
    _window = Window::GetInstancePtr();
    _window->Create(COMETA_DEFAULT_WIDTH, COMETA_DEFAULT_HEIGHT, "CometA");

}

void Renderer::Update(){

    // Update current window
    _window->Update();


    // Check if window must close
    // !glfwWindowShouldClose(this->_window);

}

/**
 * Close all the rendering artifacts created
 * And terminate the Graphics library
 */
void Renderer::Close(){
    _window->Close();
    glfwTerminate();
}


