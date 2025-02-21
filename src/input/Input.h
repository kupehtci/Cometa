#ifndef COMETA_INPUT_H
#define COMETA_INPUT_H

#include "../core/Singleton.h"

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
   std::unordered_map<int, int> _keys; 

   bool IsKeyPressed(int keycode);
   bool IsKeyReleased(int keycode);
   bool IsMouseButtonPressed(int button);

   glm::vec2 GetMousePosition();
   glm::vec2 GetMouseScroll();
}; 

#endif // COMETA_INPUT_H