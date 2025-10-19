#pragma once

#include <GLFW/glfw3.h>

/**
 * @class Window
 * @brief Manages the application window, OpenGL context, and screen-related operations.
 *
 * The Window class provides a wrapper around GLFW for creating and managing
 * an OpenGL rendering window. It handles input polling, window resizing,
 * and buffer management. This class follows a singleton pattern accessible via Window::Get().
*/
class Window
{
private:
    /**
     * @brief Pointer to the underlying GLFW window instance.
     */
    GLFWwindow* glfwWindow{nullptr};

    /**
     * @brief Singleton instance of the Window.
     */
    static Window* instance;

    /**
     * @brief Current width of the application window.
     */
    int screenWidth{0};

    /**
     * @brief Current height of the application window.
     */
    int screenHeight{0};

public:
    /**
     * @brief Retrieves the global Window instance.
     * @return Pointer to the active Window instance.
     */
    static Window* Get() { return instance; }

    /**
     * @brief Constructs and initializes the application window.
     *
     * Creates a GLFW window, sets up an OpenGL context, and registers resize callbacks.
     * Throws a runtime error if GLFW fails to initialize or a window already exists.
     *
     * @param p_screenWidth Initial width of the window.
     * @param p_screenHeight Initial height of the window.
     * @param title Title of the window.
     *
     * @throws std::runtime_error If GLFW initialization or window creation fails.
     */
    Window(int p_screenWidth, int p_screenHeight, const char* title);

    /**
     * @brief Destroys the GLFW window and cleans up resources.
     */
    ~Window();

    /**
     * @brief Returns the internal GLFW window pointer.
     * @return Pointer to the underlying GLFWwindow object.
     */
    GLFWwindow* GetGlfwWindow() { return glfwWindow; }

    /**
     * @brief Clears the framebuffer using the configured clear color in render settings.
     */
    void Clear();

    /**
     * @brief Polls system and input events.
     *
     * Should be called once per frame, typically before rendering.
     */
    void PollEvents();

    /**
     * @brief Checks if the window should close.
     * @return True if the user has requested to close the window.
     */
    bool ShouldClose();

    /**
     * @brief Swaps the front and back buffers.
     *
     * Should be called once per frame after rendering.
     */
    void SwapBuffers();

    /**
     * @brief Updates the internal screen dimensions and viewport size.
     * @param p_screenWidth New width of the window.
     * @param p_screenHeight New height of the window.
     */
    void UpdateScreenSize(int p_screenWidth, int p_screenHeight);

    /**
     * @brief GLFW resize callback function.
     *
     * Updates the associated Window instance when the window is resized.
     * @param window Pointer to the GLFW window.
     * @param width New width of the window.
     * @param height New height of the window.
     */
    static void ResizeCallback(GLFWwindow* window, int width, int height);

    /**
     * @brief Gets the current screen width.
     * @return The width of the window in pixels.
     */
    int GetScreenWidth() { return screenWidth; }

    /**
     * @brief Gets the current screen height.
     * @return The height of the window in pixels.
     */
    int GetScreenHeight() { return screenHeight; }
};
