//
// Created by Daniel Laplana Gimeno on 19/1/25.
//

#include "Window.h"

#include <iostream>


// Its implemented at the end of the file
void HandleResizeCallback(GLFWwindow *window, int width, int height);


void Window::Create(int width, int height, const char *title) {

    // Store resolution parameters
    _resolution = new Quad(width, height);


    // Create a GLFW window
    this->_window = glfwCreateWindow(width,height, title, NULL, NULL);

    if (!_window) {
        glfwTerminate();
        return;
    }

    glfwSetWindowSizeCallback(_window, HandleResizeCallback);

    glfwMakeContextCurrent(_window);
}

void Window::Update() {
    Render();
}

void Window::Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    // OpenGL drawing commands...

    glfwSwapBuffers(_window);
    glfwPollEvents();
}

bool Window::ShouldHandleCloseWindow(){
    return !glfwWindowShouldClose(this->_window);
}

/**
 * Close the window and clean it
 */
void Window::Close() {
    glfwDestroyWindow(_window);
}

/**
 * Handle the resize of the window
 */
void Window::HandleResize(GLFWwindow* window, int width, int height) {
    Quad previousResolution = *_resolution;

    glfwGetWindowSize(_window, &_resolution->x, &_resolution->y);

    std::cout << "Handling resize from " << previousResolution.x << ", " << previousResolution.y << " to " << _resolution->x << ", " << _resolution->y << std::endl;
}

/**
 * Callback that is called from GLFW library and calls the Window HandleResize method to handle the resize of the window
 * @param window
 * @param width
 * @param height
 */
void HandleResizeCallback(GLFWwindow* window, int width, int height){
    Window::GetInstancePtr()->HandleResize(window, width, height);
}