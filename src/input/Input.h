#ifndef COMETA_INPUT_H
#define COMETA_INPUT_H

#include "../core/Singleton.h"
#include "../render/Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

enum InputType{
    KEY_PRESSED = 1,
    KEY_RELEASED = 2,
    KEY_HOLD = 3, // ¿?
    MOUSE_MOVED = 4,
    MOUSE_BUTTON_PRESSED = 5,
    MOUSE_BUTTON_RELEASED = 6, 
    MOUSE_SCROLL = 7,
}; 

class Input : public Singleton<Input>{
private: 
    // std::unordered_map<int, int> _keys; 
    // GLFWwindow* _window;                   // Window is created by Rendered and passed to input initialization


public: 
    // Input(); 

   static bool IsKeyPressed(int keycode);
   static bool IsMouseButtonPressed(int button);
   static bool IsKeyReleased(int keycode);

   static glm::vec2 GetMousePosition();
   static glm::vec2 GetMouseScroll();

   // void SetWindowContext(GLFWwindow* window);
}; 

#endif // COMETA_INPUT_H