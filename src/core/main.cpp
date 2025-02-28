//
//// #define GLFW_INCLUDE_VULKAN
//

#include "../core/Application.h"

#include <filesystem>
#include <iostream>

#include "../debug/Assertion.h"

#include "layer_system/Onion.h"

class ExampleLayer : public Layer{

public: 
    ExampleLayer() = default;

    void Init() override {
        std::cout << "Example Layer Init" << std::endl;
    }
    void Update() override {
        std::cout << "Example Layer Update" << std::endl;
    }
    void Close() override {
        std::cout << "Example Layer Close" << std::endl;
    }

    void HandleEvent(Event& event){
        std::cout << "Event handled: " << event.GetEventType() << std::endl;
        event.SetHandled();
    }
}; 


int main() {

    Onion lOnion = Onion();
    lOnion.PushLayer(new ExampleLayer());
    Layer* layer2 = new ExampleLayer(); 
    lOnion.PushLayer(layer2);

    lOnion.Init();
    
    lOnion.PopLayer(layer2); 

    lOnion.Update();
    
    lOnion.Close();

    // Application* app = Application::GetInstancePtr();
    // app->Init();
    // app->Running();
    // app->Close();

    return 0;
}

