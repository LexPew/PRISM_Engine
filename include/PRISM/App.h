#pragma once

//Includes
#include <glad/glad.h>
#include <PRISM/Core/Window.h>
#include <memory>

/**
 * @class App
 * @brief Main application class for the PRISM engine.
 *
 * This class manages the initialization and execution of the PRISM engine, including setting up the window,
 * rendering the scene, and handling user input.
 */
class App
{
private:
    std::shared_ptr<Window> window{nullptr}; // A shared pointer to the main application window.

    int screenWidth = 1280; // The width of the screen in pixels.
    int screenHeight = 720; // The height of the screen in pixels.
    float fov = 45.0f;      // The field of view angle for the camera.
public:
    /**
     * @brief Runs the main application loop.
     *
     * This function handles user input and updates the renderer to display the current frame. It also manages the window's event queue.
     * The loop continues until the window is closed by the user.
     *
     * @return true if the application runs successfully, false otherwise.
     */
    bool Run();

private:
    /**
     * @brief Initializes the application by creating a window and setting up necessary components.
     *
     * This function sets up the window, initializes GLAD to load OpenGL functions, and creates a renderer instance.
     * It also configures the main camera for the scene.
     *
     * @return true if initialization is successful, false otherwise.
     */
    bool Init();
    /**
     * @brief Main application loop that handles user input and updates the renderer.
     *
     * This function is called repeatedly in the main loop of the application to handle events, update the scene, and render frames.
     */
    void Loop();

    void ShutDown();
};