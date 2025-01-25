////
////// #define GLFW_INCLUDE_VULKAN
////
//
//#include <GLFW/glfw3.h>
////#include <glad/glad.h> // Optional if you use GLAD for loading OpenGL extensions
//
//#include "../core/Application.h"
//
//int main() {
////    // Initialize GLFW
////    if (!glfwInit()) {
////        return -1;
////    }
////
////    // Create a GLFW window
////    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
////    if (!window) {
////        glfwTerminate();
////        return -1;
////    }
////
////    // Make the context current
////    glfwMakeContextCurrent(window);
////
////
//////    // Optionally load OpenGL functions using GLAD
//////    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//////        return -1;
//////    }
////
////    // Main loop
////    while (!glfwWindowShouldClose(window)) {
////        glClear(GL_COLOR_BUFFER_BIT);
////
////        // OpenGL drawing commands...
////
////        glfwSwapBuffers(window);
////        glfwPollEvents();
////    }
////
////    glfwDestroyWindow(window);
////    glfwTerminate();
////    return 0;
//
//    Application* app = Application::GetInstancePtr();
//    app->Init();
//    app->Running();
//    app->Close();
//
//    return 0;
//}


#define GLAD_GL_IMPLEMENTATION
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>



static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);



    while (!glfwWindowShouldClose(window))
    {

  
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}