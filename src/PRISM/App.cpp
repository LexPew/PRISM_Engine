#include <PRISM/App.h>
#include <PRISM/Utils/FLoader.h>
#include <PRISM/Utils/PMath.h>
#include <PRISM/Renderer/Shader.h>
#include <PRISM/Examples/CubeScene.h>
#include <fmt/core.h>

#include <PRISM/Engine/ModelEntity.h>
#include <PRISM/Engine/CameraEntity.h>
#include <PRISM/Renderer/Cube.h>




// Variables

std::unique_ptr<Shader> defaultShader = nullptr;
bool App::Run()
{
    Mouse mouse;
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

    // Initialize the renderer
    renderer = std::make_unique<Renderer>( window);

    //Init PMath
    PMath::InitializeRandom((float)glfwGetTime());

    Loop();
    return true;
}

void App::Loop()
{

    CubeScene scene;
        scene.Start();
         double lastTime = glfwGetTime();

    while (!window->ShouldClose())
    {
        double currentTime = glfwGetTime();
        float deltaTime = float(currentTime - lastTime);
        lastTime = currentTime;
  
        // Logic
        
        scene.Update(deltaTime);
 
        // Rendering

        renderer->BeginFrame();
        scene.Draw();

    
        renderer->EndFrame();
    }
}