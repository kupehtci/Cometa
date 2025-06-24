#ifndef COMETA_APPLICATION_H
#define COMETA_APPLICATION_H

//#include "Singleton.h"
#include "render/Renderer.h"
#include "Time.h"
#include "input/Input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "layer_system/Onion.h"
#include "world/WorldManager.h"
#include "physics/PhysicsManager.h"
#include "world/ScriptSystem.h"

/**
 * Application is the entry point for Cometa Framework
 * It's in charge of initializing, control the lifecycle of all the managers and close them under application shutdown
 */
class Application : public Singleton<Application>{
    friend class Window;
    friend class Input;
    friend class Renderer;
    friend class WorldManager;
    friend class PhysicsManager;
    friend class ScriptManager;

private :
    /**
     * Boolean that is true when the application is running.
     * Its checked every frame if the application should close
     */
    bool _isRunning;

    // Managers
    WorldManager* _worldManager = nullptr;
    Renderer* _renderer = nullptr;
    PhysicsManager* _physicsManager = nullptr;
    Time* _time = nullptr;
    Input* _input = nullptr;
    ScriptManager* _scriptManager = nullptr;


    Onion _onion;

public:
    Application();
    ~Application() final;

public:
    /**
     * Initialize the application
     */
    void Init();

    /**
     * Keeps the application running and checking if should close
     */
    void Running();

    /**
     * Close the application by closing all the managers
     */
    void Close();

    // ------------ GETTERS ------------

    /**
     * Retrieve the Onion (Layer stack) of the application
     * @return {Onion*} pointer to the onion stored within the class.
     */
    Onion* GetOnion() { return &_onion; }

private:
    /**
     * Set isRunning to false so in next frame application will close
     */
    void MustClose(){
        _isRunning = false;
    }
};


#endif //COMETA_APPLICATION_H
