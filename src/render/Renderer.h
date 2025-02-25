
// Created by Daniel Laplana Gimeno on 5/12/24.
//

// #define GL_SILENCE_DEPRECATION

#define GLAD_GL_IMPLEMENTATION
#define GLFW_INCLUDE_NONE


#include "core/Singleton.h"
#include "../math/Quad.h"
#include "./Window.h"

#ifndef AURAGL_RENDERER_H
#define AURAGL_RENDERER_H

const unsigned int COMETA_DEFAULT_WIDTH = 1600;
const unsigned int COMETA_DEFAULT_HEIGHT = 900;


class Renderer : public SingletonManager<Renderer>//public Singleton<Renderer>
{
    friend class Application;

private:
    Window* _window;
    Shader* _objectShader;      // Main object shader using camera and fragment shader

public:
    Renderer();
    ~Renderer();

public:
    void Init() override;
    void Update() override;
    void Close() override;

    inline Window* GetWindow(){ return _window; }
    inline Shader* GetObjectShader(){ return _objectShader; }
};


#endif //AURAGL_RENDERER_H
