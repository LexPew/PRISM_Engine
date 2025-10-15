#pragma once

#include <GLFW/glfw3.h>

class Window
{
private:
    GLFWwindow *window{nullptr};

public:
    int screenWidth{0};
    int screenHeight{0};

    Window(int p_screenWidth, int p_screenHeight, const char *title);
    ~Window();


    GLFWwindow *GetGlfwWindow() { return window; };

    void Clear();
    void PollEvents();
    bool ShouldClose();
    void SwapBuffers();

    static void ResizeCallback(GLFWwindow *window, int width, int height);
};