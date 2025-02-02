//
// Created by Daniel Laplana Gimeno on 19/1/25.
//

#ifndef AURAGL_WINDOW_H
#define AURAGL_WINDOW_H

#include "../math/Quad.h"
#include "../core/Singleton.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window : public Singleton<Window>{
private:
    GLFWwindow* _window;
    Quad* _resolution;
    const char* _title;

public:
    Window(); 
    ~Window();

    /**
     * Create a new Window by settting the width, height and window's title
     * @param width (int) width of the window
     * @param height (int) height of the window
     * @param title (const char*) title of the window
     */
    void Create(int width, int height, const char* title);

    /**
     * Update the window's state
     */
    void Update();

    /**
     * Render the window's elements
     */
    void Render();

    /**
     * Close the window and remove its instance
     */
    void Close();

    // Check if window should close
    bool ShouldHandleCloseWindow();

    // GETTERS AND SETTERS
public:
    /**
     * Get the current resolution of the window
     * @return
     */
    inline Quad GetCurrentResolution(){
        return *_resolution;
    }

    /**
     * Get the current title of the window
     * @return
     */
    inline const char* GetTitle(){
        return _title;
    }

public:
    /**
     * Handle the resize of the window
     * This function is used through the HandleResizeCallback function
     */
     void HandleResize(GLFWwindow* window, int width, int height);


};


#endif //AURAGL_WINDOW_H
