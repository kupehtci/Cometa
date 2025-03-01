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

    _position = glm::vec3(0.0f, 0.0f, 0.0f);
    _up = glm::vec3(0.0f, 1.0f, 0.0f);

    _direction = glm::vec3(0.0f, 0.0f, 1.0f);
    _right = glm::cross(_direction, glm::vec3(0.0f, 1.0f, 0.0f));


    _movementSpeed = 0.3f;
    _sensitivity = 0.1f; 
    
    _pitch = 0.0f; 
    _yaw = -90.0f;
    _fov = 45.0f;

    _near = 0.05f;
    _far = 1000.0f;

    // Coordinate matrices
    // Quad currentResolution = Renderer::GetInstancePtr()->GetWindow()->GetCurrentResolution();
    _projectionMatrix = glm::perspective(glm::radians(_fov), static_cast<float>((float)COMETA_DEFAULT_WIDTH/(float)COMETA_DEFAULT_HEIGHT), _near, _far);

    _viewMatrix = glm::translate(glm::mat4(1.0f), _direction * 3.0f); //glm::translate(view, glm::vec3(0.0f, 0.0f, glm::cos((float)glfwGetTime()) *  -2.0f - 5.0f));
}

Camera::Camera(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {

    _movementSpeed = 13.0f;
    _sensitivity = 0.2f;

    _pitch = 0.0f;
    _yaw = -90.0f;
    _fov = 45.0f;

    _near = 0.05f;
    _far = 1000.0f;


    _position = glm::vec3(0.0f, 0.0f, 3.0f);
    _up = glm::vec3(0.0f, 1.0f, 0.0f);

    _direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _direction.y = sin(glm::radians(_pitch));
    _direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

    _direction = glm::normalize(_direction);

    // _direction = glm::vec3(0.0f, 0.0f, -1.0f);
    _right = glm::cross(_direction, _up);




    _projectionMatrix = projectionMatrix;

    _viewMatrix = viewMatrix;
}

Camera::~Camera() {

}

void Camera::OnUpdate() {

    _right = glm::normalize(glm::cross(_up, _direction)); 

    if(Input::IsKeyPressed(GLFW_KEY_W)) {
        _position += _direction * _movementSpeed * Time::GetDeltaTime();
    }
    if(Input::IsKeyPressed(GLFW_KEY_S)) {
        _position -= _direction * _movementSpeed * Time::GetDeltaTime();
    }
    if(Input::IsKeyPressed(GLFW_KEY_A)) {
        _position += _right * _movementSpeed * Time::GetDeltaTime();
    }
    if(Input::IsKeyPressed(GLFW_KEY_D)) {
        _position -= _right * _movementSpeed * Time::GetDeltaTime();
    }


    // Update direction
    std::cout << " camera yaw: " << _yaw << " and pitch " << _pitch << std::endl;

    glm::vec2 mouseDelta = Input::GetMouseDelta();

    _yaw += (mouseDelta.x * _sensitivity);
    _pitch -= (mouseDelta.y * _sensitivity);

    _pitch = CometaMath::Scope(_pitch, -89.0f, 89.0f);


    _direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _direction.y = sin(glm::radians(_pitch));
    _direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

    _direction = glm::normalize(_direction); 
    

    // Update shader coordinates system
    Quad currentResolution = Renderer::GetInstancePtr()->GetWindow()->GetCurrentResolution();
    _projectionMatrix = glm::perspective(glm::radians(_fov), static_cast<float>((float)currentResolution.x / (float)currentResolution.y), _near, _far);

    _viewMatrix = glm::lookAt(_position, _position + _direction, _up); // glm::translate(glm::mat4(1.0f), _direction );
}




