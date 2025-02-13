//
// Created by Daniel Laplana Gimeno on 12/2/25.
//

#include "Camera.h"

Camera::Camera() {
    _projectionMatrix = glm::mat4(1.0f);

    glm::mat4 view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    // _viewMatrix = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
}

Camera::Camera(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {
    _projectionMatrix = projectionMatrix;

    _viewMatrix = viewMatrix;
}

