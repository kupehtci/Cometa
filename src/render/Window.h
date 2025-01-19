//
// Created by Daniel Laplana Gimeno on 19/1/25.
//

#ifndef AURAGL_WINDOW_H
#define AURAGL_WINDOW_H

#include "../math/Quad.h"
#include "../core/Singleton.h"
#include <GLFW/glfw3.h>

class Window : public Singleton<Window>{
private:
    GLFWwindow* _window;
    Quad* _resolution;
    const char* _title;

public:
    void Create(int width, int height, const char* title);
    void Update();
    void Render();
    void Close();

    // Check if window should close
    bool ShouldHandleCloseWindow();

    // GETTERS AND SETTERS
    Quad GetCurrentResolution(){
        return *_resolution;
    }

public:
    /**
     * Handle the resize of the window
     * This function is used through the HandleResizeCallback function
     */
     void HandleResize(GLFWwindow* window, int width, int height);


};


#endif //AURAGL_WINDOW_H
