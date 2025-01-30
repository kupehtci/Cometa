//
//// #define GLFW_INCLUDE_VULKAN
//

#include "../core/Application.h"

int main() {
    Application* app = Application::GetInstancePtr();
    app->Init();
    app->Running();
    app->Close();

    return 0;
}

