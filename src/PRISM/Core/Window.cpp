#include <glad/glad.h>
#include <PRISM/Core/Window.h>
#include <fmt/core.h>

Window::Window(int screenWidth, int screenHeight, const char *title)
{
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
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    glViewport(0, 0, width, height);
}
