#pragma once

#include <GLFW/glfw3.h>

class Window
{
private:
    GLFWwindow *glfwWindow{nullptr};
    static Window *instance;


    int screenWidth{0};
    int screenHeight{0};
public:
    static Window *Get() { return instance; }


    Window(int p_screenWidth, int p_screenHeight, const char *title);
    ~Window();

    GLFWwindow *GetGlfwWindow() { return glfwWindow; }

    void Clear();
    void PollEvents();
    bool ShouldClose();
    void SwapBuffers();
    void UpdateScreenSize(int p_screenWidth, int p_screenHeight);
    static void ResizeCallback(GLFWwindow *window, int width, int height);

    int GetScreenWidth(){return screenWidth;};
    int GetScreenHeight(){return screenHeight;};
};
