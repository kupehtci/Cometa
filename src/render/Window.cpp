//
// Created by Daniel Laplana Gimeno on 19/1/25.
//
#define GL_SILENCE_DEPRECATION

#include "Window.h"
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

// Window constructor
Window::Window()
{
    this->_resolution = nullptr; 
    this->_window = nullptr;
    this->_title = "none";
}

/**
 * Window destructor
 */
Window::~Window(){
//    if(this->_window !=  nullptr){
//        glfwDestroyWindow(this->_window);
//    }
//
//    delete this->_resolution;
//    delete this->_title;
}

/**
 * Callback to handle the window resize through OpenGL function
 * @param window Window pointer passed through the OpenGL callback
 * @param width New width passed through the OpenGL callback
 * @param height New height passed through the OpenGL callback
 */
void HandleResizeCallback(GLFWwindow *window, int width, int height);



void Window::Create(int width, int height, const char *title) {

    // Store resolution parameters
    _resolution = new Quad(width, height);
    this->_title = title;


    // Create a GLFW window
    this->_window = glfwCreateWindow(width,height, title, NULL, NULL);

    if (!_window) {
        glfwTerminate();
        return;
    }

    // Set Callbacks
    glfwSetWindowSizeCallback(_window, HandleResizeCallback);


    glfwMakeContextCurrent(_window);
}

void Window::Update() {
    Render();
}

void Window::Render() {

    glClearColor(0.2f, 0.1f, 0.3f, 1.0f); // Set background color
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the screen


    // ------------------------------------------------------------------------------------
    // TESTING

    unsigned int vertexShaderID;
    unsigned int fragmentShaderID;
    unsigned int shaderProgramID;

    // Error handling variables
    int  success;
    char infoLog[512];

    // Compile vertex shader
    Shader vertexShader = Shader("src/render/shaders/vertex_shader.vert", GL_VERTEX_SHADER);
    vertexShaderID = vertexShader.GetShaderUID();

    Shader fragShader = Shader("src/render/shaders/fragment_shader.frag", GL_FRAGMENT_SHADER);
    fragmentShaderID = fragShader.GetShaderUID();


    // Attach both shaders as a single Shader Program
    shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShaderID);
    glAttachShader(shaderProgramID, fragmentShaderID);
    glLinkProgram(shaderProgramID);

    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
        std::cout << "ERROR/SHADER/PROGRAM/LINKING_FAILED" << std::endl << infoLog << std::endl;
    }


    // Set shader as current and delete the compiled shaders
    glUseProgram(shaderProgramID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);


    float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left
            0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // right
            0.0f,  0.5f, 0.0f ,  0.0f, 0.0f, 1.0f, // top
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attr
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attr
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw our first triangle
    glUseProgram(shaderProgramID);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);


    // Once all is used, delete the resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgramID);

    // ------------------------------------------------------------------------------------



    glfwSwapBuffers(_window);
    glfwPollEvents();

}

bool Window::ShouldHandleCloseWindow(){
    return !glfwWindowShouldClose(this->_window);
}

/**
 * Close the window and clean it
 * Also clean the rest of parameters of the window
 */
void Window::Close() {

    if(this->_window !=  nullptr){
        glfwDestroyWindow(this->_window);
    }

    delete this->_resolution;
    this->_resolution = nullptr;
    // delete this->_title;
    // this->_title = nullptr;
}

/**
 * Handle the resize of the window
 */
void Window::HandleResize(GLFWwindow* window, int width, int height) {
    Quad previousResolution = *_resolution;

    glfwGetWindowSize(_window, &_resolution->x, &_resolution->y);

    std::cout << "Handling resize from " << previousResolution.x << ", " << previousResolution.y << " to " << _resolution->x << ", " << _resolution->y << std::endl;

    // modify viewport resolution
    glViewport( 0.f, 0.f, _resolution->x, _resolution->y);
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