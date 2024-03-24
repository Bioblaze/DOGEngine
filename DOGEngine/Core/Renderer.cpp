#include "Renderer.h"
#include <mutex>
#include <stdexcept>

#include "GLFW/glfw3.h"
#include <iostream>
Renderer& Renderer::getInstance() {
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex); // Lock for thread safety
    static Renderer instance; // C++11 magic statics for thread-safe initialization
    return instance;
}

Renderer::Renderer() : window(nullptr) {
    // Initialization code if needed
}

Renderer::~Renderer() {
    // Cleanup code if needed, e.g., glfwDestroyWindow(window);
    glfwTerminate();
}

void Renderer::CreateWindow(const char* title, int width, int height) {
    if (!window) { // Check if window is already created
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return; // Or handle the failure as needed
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }
        glfwMakeContextCurrent(window);
        // Initialization for GLEW or other libraries can be added here
    }
}

GLFWwindow* Renderer::GetWindow() const {
    return window;
}
