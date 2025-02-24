//
// Created by Daniel Laplana Gimeno on 12/2/25.
//

#include "Camera.h"
#include "Window.h"
#include "Renderer.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "../input/Input.h"

#include "../math/CometaMath.h"

Camera::Camera() {

    _position = glm::vec3(0.0f, 0.0f, 3.0f);
    _up = glm::vec3(0.0f, 1.0f, 0.0f);

    _direction = glm::vec3(0.0f, 0.0f, -1.0f);
    _right = glm::cross(_direction, glm::vec3(0.0f, 1.0f, 0.0f));


    _movementSpeed = 7.0f;
    _sensitivity = 0.1f; 
    
    _pitch = 0.0f; 
    _yaw = -90.0f; 
    _fov = 45.0f;

    _near = 0.05f;
    _far = 1000.0f;

    // Coordinate matrices
    Quad currentResolution = Renderer::GetInstancePtr()->GetWindow()->GetCurrentResolution();
    _projectionMatrix = glm::perspective(glm::radians(30.0f), static_cast<float>((float)currentResolution.x/(float)currentResolution.y), 0.1f, 100.0f);// glm::mat4(1.0f);

    glm::mat4 view = glm::mat4(1.0f);

    _viewMatrix = glm::translate(glm::mat4(1.0f), _direction * 3.0f); //glm::translate(view, glm::vec3(0.0f, 0.0f, glm::cos((float)glfwGetTime()) *  -2.0f - 5.0f));
}

Camera::Camera(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {
    _projectionMatrix = projectionMatrix;

    _viewMatrix = viewMatrix;
}

Camera::~Camera() {

}

void Camera::OnUpdate() {
    if(Input::IsKeyPressed(GLFW_KEY_W)) {
        _viewMatrix = glm::translate(_viewMatrix, glm::vec3(0.0f, 0.0f, -0.1f));
    }
    if(Input::IsKeyPressed(GLFW_KEY_S)) {
        _viewMatrix = glm::translate(_viewMatrix, glm::vec3(0.0f, 0.0f, 0.1f));
    }
    if(Input::IsKeyPressed(GLFW_KEY_A)) {
        _viewMatrix = glm::translate(_viewMatrix, glm::vec3(-0.1f, 0.0f, 0.0f));
    }
    if(Input::IsKeyPressed(GLFW_KEY_D)) {
        _viewMatrix = glm::translate(_viewMatrix, glm::vec3(0.1f, 0.0f, 0.0f));
    }


    // Update direction

    _direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _direction.y = sin(glm::radians(_pitch));
    _direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

    glm::vec2 mouseDelta = Input::GetMouseDelta(); 

    _yaw += (mouseDelta.x * _sensitivity);
    _pitch += (mouseDelta.y * _sensitivity); 


    // Update shader coordinates system

}

