#include <glad/glad.h>
#include <PRISM/Core/Window.h>
#include <fmt/core.h>
#include <PRISM/Renderer/RenderSettings.h>


Window *Window::instance = nullptr;
// TODO: UPDATE THIS TO USE BETTE THAN RUNTIME ERROR AND SORT INCLUDES ETC, also add comments
Window::Window(int p_screenWidth, int p_screenHeight, const char *title)
{

    if (instance != nullptr)
    {
        fmt::println("Error: Window already exists!");
        throw std::runtime_error("Window singleton already created");
    }
    instance = this;

    screenWidth = p_screenWidth;
    screenHeight = p_screenHeight;

    if (!glfwInit())
    {
        fmt::println("Error: GLFW failed to initialize");
        throw std::runtime_error("GLFW init failed");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindow = glfwCreateWindow(screenWidth, screenHeight, title, nullptr, nullptr);
    if (!glfwWindow)
    {
        fmt::println("Error: Failed to create window");
        glfwTerminate();
        throw std::runtime_error("Window creation failed");
    }

    glfwMakeContextCurrent(glfwWindow);
    glfwSetWindowUserPointer(glfwWindow, this);
    glfwSetWindowSizeCallback(glfwWindow, ResizeCallback);
}

Window::~Window()
{
    if (glfwWindow)
    {
        glfwDestroyWindow(glfwWindow);
        glfwWindow = nullptr;
    }

    glfwTerminate();
    instance = nullptr;
}

void Window::Clear()
{
    glClearColor(
        RenderSettings::clearColor.r,
        RenderSettings::clearColor.g,
        RenderSettings::clearColor.b,
        RenderSettings::clearColor.z);

    GLbitfield mask = GL_COLOR_BUFFER_BIT;
    if (RenderSettings::testDepth)
        mask |= GL_DEPTH_BUFFER_BIT;

    glClear(mask);
}

void Window::PollEvents() { glfwPollEvents(); }
bool Window::ShouldClose() { return glfwWindowShouldClose(glfwWindow); }
void Window::SwapBuffers() { glfwSwapBuffers(glfwWindow); }

void Window::ResizeCallback(GLFWwindow *window, int width, int height)
{
    auto appWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));
    if (appWindow)
    {
        appWindow->UpdateScreenSize(width, height);
    }

}
void Window::UpdateScreenSize(int p_screenWidth, int p_screenHeight)
{
    screenWidth = p_screenWidth;
    screenHeight = p_screenHeight;
        glViewport(0, 0, screenWidth, screenHeight);
}
