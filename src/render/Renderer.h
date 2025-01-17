
// Created by Daniel Laplana Gimeno on 5/12/24.
//

#include "core/Singleton.h"
#include <GLFW/glfw3.h>

#ifndef AURAGL_RENDERER_H
#define AURAGL_RENDERER_H

struct Quad {
    int x;
    int y;

    inline explicit Quad(int x = 1920, int y = 1080){
        this->x = x;
        this->y = y;
    }
};

class Renderer : public SingletonManager<Renderer>//public Singleton<Renderer>
        {
    friend class Application;

private:
    GLFWwindow* _window;
    Quad* _resolution;

public:
    Renderer();
    ~Renderer();

public:
    void Init();
    void Update();
    void Close();
};


#endif //AURAGL_RENDERER_H
