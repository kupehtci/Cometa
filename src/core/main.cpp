//
//// #define GLFW_INCLUDE_VULKAN
//

#include "../core/Application.h"

#include <filesystem>
#include <iostream>

#include "../debug/Assertion.h"

int main() {

    Application* app = Application::GetInstancePtr();
    app->Init();
    app->Running();
    app->Close();

    return 0;
}

