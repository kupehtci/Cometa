//
// Created by Daniel Laplana Gimeno on 18/11/24.
//

//#include "Singleton.h"
#include "render/Renderer.h"
#include "Time.h"
#include "input/Input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifndef AURAGL_APPLICATION_H
#define AURAGL_APPLICATION_H



class Application : public Singleton<Application>{
private :
    bool _isRunning;
    Renderer* _renderer;
    Time* _time; 
    Input* _input; 


public:
    Application();
    ~Application();

public:
    void Init();
    void Running();
    void Close();

};


#endif //AURAGL_APPLICATION_H
