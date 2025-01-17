//
//// #define GLFW_INCLUDE_VULKAN
//

#include <GLFW/glfw3.h>
//#include <glad/glad.h> // Optional if you use GLAD for loading OpenGL extensions

#include "../core/Application.h"

int main() {
//    // Initialize GLFW
//    if (!glfwInit()) {
//        return -1;
//    }
//
//    // Create a GLFW window
//    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
//    if (!window) {
//        glfwTerminate();
//        return -1;
//    }
//
//    // Make the context current
//    glfwMakeContextCurrent(window);
//
//
////    // Optionally load OpenGL functions using GLAD
////    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
////        return -1;
////    }
//
//    // Main loop
//    while (!glfwWindowShouldClose(window)) {
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // OpenGL drawing commands...
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    glfwDestroyWindow(window);
//    glfwTerminate();
//    return 0;

    Application* app = Application::GetInstancePtr();
    app->Init();
    app->Running();
    app->Close();

    return 0;
}
