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
    // 1. Create the window first
    window = std::make_shared<Window>(screenWidth, screenHeight, "PRISM");

    // 2. Load GL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fmt::println("Failed to load GLAD");
        return false;
    }

    // 3. Initialize renderer
    renderer = std::make_unique<Renderer>(window);

    // 4. Initialize input system 
    input = std::make_unique<Input>();


    // 6. Initialize math, scenes, etc.#
    float randomSeed = (float)glfwGetTime();
    randomSeed += (float)clock();
    PMath::InitializeRandom(randomSeed);

    // 7. Run main loop
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
  

 
        // Rendering

        renderer->BeginFrame();

        // Logic
        input->Update(window->GetGlfwWindow());
        scene.Update(deltaTime);

        scene.Draw();

    
        renderer->EndFrame();
            input->EndFrame();
    
    }
}