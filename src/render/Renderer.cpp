//
// Created by Daniel Laplana Gimeno on 5/12/24.
//

#include "Renderer.h"
#include "../debug/Assertion.h"
#include <GLFW/glfw3.h>

Renderer::Renderer() {
    this->_window = nullptr;
    this->_resolution = new Quad(800, 600);
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

    // Create a GLFW window
    this->_window = glfwCreateWindow(_resolution->x, _resolution->y, "CometA", NULL, NULL);
    if (!_window) {
        glfwTerminate();
        return;
    }

}

void Renderer::Update(){

    glClear(GL_COLOR_BUFFER_BIT);

    // OpenGL drawing commands...


    // EXAMPLE  DRAWING A TRIANGLE
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
    };

    // Generate a buffer that is signed by an unique ID
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // Bind the buffer to an array buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Copy the vertices data into the Buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glfwSwapBuffers(this->_window);
    glfwPollEvents();

    // Check if window must close
    // !glfwWindowShouldClose(this->_window);
}

void Renderer::Close(){
    glfwDestroyWindow(this->_window);
    glfwTerminate();
}


