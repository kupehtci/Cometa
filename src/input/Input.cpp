#include "Input.h"


bool Input::IsKeyPressed(int keycode){
    GLFWwindow* currentWindow = Renderer::GetInstancePtr()->GetWindow()->GetGlfwWindow(); 
    return (glfwGetKey(currentWindow, keycode) == GLFW_PRESS); 
}

bool Input::IsKeyReleased(int keycode){
    GLFWwindow* currentWindow = Renderer::GetInstancePtr()->GetWindow()->GetGlfwWindow();
    return (glfwGetKey(currentWindow, keycode) == GLFW_RELEASE);
}

bool Input::IsMouseButtonPressed(int button){
    GLFWwindow* currentWindow = Renderer::GetInstancePtr()->GetWindow()->GetGlfwWindow();
    return (glfwGetMouseButton(currentWindow, button) == GLFW_PRESS);
}

glm::vec2 Input::GetMousePosition(){
    GLFWwindow* currentWindow = Renderer::GetInstancePtr()->GetWindow()->GetGlfwWindow();
    double xpos, ypos;
    glfwGetCursorPos(currentWindow, &xpos, &ypos);
    return glm::vec2(xpos, ypos);
}

// Under development
glm::vec2 Input::GetMouseScroll(){
    GLFWwindow* currentWindow = Renderer::GetInstancePtr()->GetWindow()->GetGlfwWindow();
    double xpos, ypos;
    //glfwGetScrollOffset(currentWindow, &xpos, &ypos);
    
    return glm::vec2(xpos, ypos);
}

