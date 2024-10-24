
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>


#include <vulkan/vulkan.h>

#include <iostream>

int main() {
    std::cout << "Hello world!" << std::endl; 
    VkInstance instance;
    VkApplicationInfo appInfo = {};
    std::cout << "Testing vulkan" << std::endl; 
}