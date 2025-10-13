#include <PRISM/App.h>
#include <PRISM/Utils/FLoader.h>
#include <PRISM/Renderer/Shader.h>
#include <PRISM/Renderer/Cube.h>

#include <fmt/core.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Variables

std::unique_ptr<Shader> defaultShader = nullptr;

bool App::Run()
{
    // Create Window
    try
    {
        window = std::make_shared<Window>(screenWidth, screenHeight, "PRISM");
    }
    catch (bool e)
    {

        return false;
    }

    // Try load glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fmt::println("Failed to load GLAD");
        return false;
    }

    camera = std::make_shared<Camera>(screenWidth, screenHeight, fov, 0.1f, 100.0f);


    //Initialize the renderer
    renderer = std::make_unique<Renderer>(camera, window);
    Loop();
    return true;
}

void App::Loop()
{

    Cube cube({0, 0, 0});
    float rotationSine = 0;
    //glm::radians(rotationSine * 180.0f)

    while (!window->ShouldClose())
    {
        renderer->BeginFrame();
        renderer->EndFrame();
    }
}