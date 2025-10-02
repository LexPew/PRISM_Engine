#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class App
{
private:
    GLFWwindow *window;

public:
    bool Run();

private:
    bool InitializeGLFW();
    void Cleanup();
    void Loop();



};