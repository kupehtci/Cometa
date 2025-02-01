//
//// #define GLFW_INCLUDE_VULKAN
//

#include "../core/Application.h"

#include <filesystem>
#include <iostream>

int main() {

    Application* app = Application::GetInstancePtr();
    app->Init();
    app->Running();
    app->Close();

    return 0;
}

