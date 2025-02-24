#include "Input.h"


void Input::Init() {

}

void Input::Update() {
    GLFWwindow* currentWindow = Renderer::GetInstancePtr()->GetWindow()->GetGlfwWindow();
    double xpos, ypos;
    glfwGetCursorPos(currentWindow, &xpos, &ypos);

    // Calculate delta movement of the mouse using previous frame mouse position
    _xDeltaPos = xpos - _xpos; 
    _yDeltaPos = ypos - _ypos; 

    _xpos = xpos;
    _ypos = ypos;

    std::cout << "Delta mouse position: (" << _xDeltaPos << " , " << _yDeltaPos << ")" << std::endl; 
}

void Input::Close() {

}

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



glm::vec2 Input::GetMouseDelta() {
    Input* lInput = Input::GetInstancePtr();

    return glm::vec2(lInput->_xDeltaPos, lInput->_yDeltaPos); 
}


