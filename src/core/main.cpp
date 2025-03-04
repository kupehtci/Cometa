//
//// #define GLFW_INCLUDE_VULKAN
//

#include "../core/Application.h"

#include <filesystem>
#include <iostream>

#include "../debug/Assertion.h"

#include "layer_system/Onion.h"
#include "layer_system/Layer.h"

#include "types/SparseSet.h"


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

    // --------- Sparse Set testing ----------

    SparseSet<int> ss; 
    ss.Add(1, 2); 
    ss.Add(2, 3);
    ss.Add(3, 5); 
    ss.Add(4, 10);
    ss.Add(5, 12);
    ss.Add(6, 14);
    ss.Add(7, 16);
    ss.Add(8, 16);
    ss.Add(9, 19);
    ss.Add(10, 23);
    ss.Add(11, 22);
    ss.Add(12, 21);
    ss.Add(13, 23);
    ss.Add(14, 32);
    ss.Pop(9);
    ss.Pop(14);
    if (ss.Contains(12)) {
        std::cout << "index 12 contains: " << ss.Get(12); 
    }
    ss.Print(); 


     //Application* app = Application::GetInstancePtr();
     //app->Init();
     //app->Running();
     //app->Close();

    return 0;
}

