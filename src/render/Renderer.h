
// Created by Daniel Laplana Gimeno on 5/12/24.
//

#include "core/Singleton.h"
#include "../math/Quad.h"
#include "./Window.h"
#include <GLFW/glfw3.h>

#ifndef AURAGL_RENDERER_H
#define AURAGL_RENDERER_H

const unsigned int COMETA_DEFAULT_WIDTH = 1600;
const unsigned int COMETA_DEFAULT_HEIGHT = 900;


class Renderer : public SingletonManager<Renderer>//public Singleton<Renderer>
        {
    friend class Application;

private:
    //GLFWwindow* _window;
    //Quad* _resolution;
    Window* _window;

public:
    Renderer();
    ~Renderer();

public:
    void Init();
    void Update();
    void Close();
};


#endif //AURAGL_RENDERER_H
