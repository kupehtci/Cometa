//
//// #define GLFW_INCLUDE_VULKAN
//

#include "../core/Application.h"

#include <filesystem>
#include <iostream>

#include "../debug/Assertion.h"

#include "layer_system/Onion.h"
#include "layer_system/Layer.h"


int main() {

//    Onion lOnion = Onion();
//    Layer* layer1 = new ExampleLayer();
//    Layer* layer2 = new ExampleLayer();
//
//    lOnion.PushLayer(layer1);
//    lOnion.PushLayer(layer2);
//
//    lOnion.Init();
//
//    lOnion.PopLayer(layer2);
//
//    lOnion.Update();
//
//    lOnion.Close();

     Application* app = Application::GetInstancePtr();
     app->Init();
     app->Running();
     app->Close();

    return 0;
}

