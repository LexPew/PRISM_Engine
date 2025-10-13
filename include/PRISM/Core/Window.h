#pragma once

#include <GLFW/glfw3.h>

class Window
{
private:
    GLFWwindow *window{nullptr};

public:
    Window(int screenWidth, int screenHeight, const char *title);
    ~Window();


    GLFWwindow *GetWindow() { return window; };

    void Clear();
    void PollEvents();
    bool ShouldClose();
    void SwapBuffers();

    static void ResizeCallback(GLFWwindow *window, int width, int height);
};