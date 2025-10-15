#include <glad/glad.h>
#include <PRISM/Core/Window.h>
#include <fmt/core.h>
#include <PRISM/Renderer/RenderSettings.h>
Window::Window(int p_screenWidth, int p_screenHeight, const char *title)
{
    screenWidth = p_screenWidth;
    screenHeight = p_screenHeight;
    // Try init GLFW
    if (!glfwInit())
    {
        fmt::println("Error: GLFW failed to initialize");
        throw(false);
    }
    // Apply window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(screenWidth, screenHeight, title, nullptr, nullptr);
    if (!window)
    {
        fmt::println("Error: Failed to create window");
        throw(false);
    }
    // Set current context to window
    glfwMakeContextCurrent(window);

    // Set Resize
    glfwSetWindowSizeCallback(window, ResizeCallback);
}

Window::~Window()
{
    if (window)
    {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void Window::Clear()
{
    // Clear screen colour to colour define in render settings
    glClearColor(
        RenderSettings::clearColor.r,
        RenderSettings::clearColor.g,
        RenderSettings::clearColor.b,
        RenderSettings::clearColor.z);

    // Change mask depending on whether we are testing for depth
    GLbitfield mask = GL_COLOR_BUFFER_BIT;

    if (RenderSettings::testDepth)
    {
        mask |= GL_DEPTH_BUFFER_BIT;
    }
    glClear(mask);
}

void Window::PollEvents()
{
    glfwPollEvents();
}
bool Window::ShouldClose()
{
    return glfwWindowShouldClose(window);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(window);
}

void Window::ResizeCallback(GLFWwindow *window, int width, int height)
{
    // I dont like this hacky way but okay
    auto appWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));
    if (appWindow)
    {
        appWindow->screenWidth = width;
        appWindow->screenHeight = height;
    }
    glViewport(0, 0, width, height);
}
