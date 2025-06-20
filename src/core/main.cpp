#include "../core/Application.h"

// Main entry point of the C++ application
// IN this file Application is created, initialized and keeps running.

int main() {

    Application* app = Application::GetInstancePtr();
    app->Init();
    app->Running();
    app->Close();

    delete app;
    
    return 0;
}

