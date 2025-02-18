//
// Created by Daniel Laplana Gimeno on 12/2/25.
//

#include "Camera.h"
#include "Window.h"
#include "Renderer.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

Camera::Camera() {
    Quad currentResolution = Renderer::GetInstancePtr()->GetWindow()->GetCurrentResolution();
    _projectionMatrix = glm::perspective(glm::radians(30.0f), static_cast<float>((float)currentResolution.x/(float)currentResolution.y), 0.1f, 100.0f);// glm::mat4(1.0f);

    glm::mat4 view = glm::mat4(1.0f);

    // note that we're translating the scene in the reverse direction of where we want to move
    _viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)); //glm::translate(view, glm::vec3(0.0f, 0.0f, glm::cos((float)glfwGetTime()) *  -2.0f - 5.0f));
}

Camera::Camera(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {
    _projectionMatrix = projectionMatrix;

    _viewMatrix = viewMatrix;
}

Camera::~Camera() {

}

void Camera::OnUpdate() {

}

