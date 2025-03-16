
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


enum FACE_CULLING_MODE {
    NONE = 0, 
    FACE_CULLING_CLOCKWISE = 1, 
    FACE_CULLING_COUNTER_CLOCKWISE = 2
};

class Renderer : public SingletonManager<Renderer>
{
    friend class Application;

private:
    Window* _window;
    Shader* _objectShader;    

    bool _depthCulling = true;
    FACE_CULLING_MODE _faceCullingMode = FACE_CULLING_MODE::FACE_CULLING_CLOCKWISE; 

public:
    Renderer();
    ~Renderer();

public:
    void Init() override;
    void Update() override;
    void Close() override;

    inline Window* GetWindow(){ return _window; }
    inline Shader* GetObjectShader(){ return _objectShader; }

    inline void SetDepthCulling(bool value) { _depthCulling = value;  }
    inline void SetFaceCulling(FACE_CULLING_MODE value) { 
        _faceCullingMode = value; 
        switch (value) {
            // TODO: Complete
        }
    }
};


#endif //AURAGL_RENDERER_H
