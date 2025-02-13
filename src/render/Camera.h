//
// Created by Daniel Laplana Gimeno on 12/2/25.
//

#ifndef AURAGL_CAMERA_H
#define AURAGL_CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

class Camera {
private:
    glm::mat4 _projectionMatrix;
    glm::mat4 _viewMatrix;
public:
    Camera();
    Camera(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);
    ~Camera();


};


#endif //AURAGL_CAMERA_H
