#ifndef RENDERER_H
#define RENDERER_H

#include "GLFW/glfw3.h"
class Renderer {
public:
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    static Renderer& getInstance();

    void CreateWindow(const char* title, int width, int height);
    GLFWwindow* GetWindow() const;

private:
    Renderer();
    ~Renderer(); // Depending on your cleanup requirements

    GLFWwindow* window;
};

#endif // RENDERER_H
