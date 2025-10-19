#include <PRISM/App.h>

#include <PRISM/Utils/PMath.h>
#include <PRISM/Examples/CubeScene.h>
#include <PRISM/Examples/TerrainScene.h>

//TODO:REmove once done testing
bool App::Init()
{
    // Initialize Everything

    // 1. Create the window first
    window = std::make_shared<Window>(screenWidth, screenHeight, " // P.R.I.S.M //");

    // 2. Load GL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        // TODO: Add Error Printing
        // fmt::println("Failed to load GLAD");
        return false;
    }

    // 3. Initialize Renderer
    renderer = std::make_unique<Renderer>();

    // 4. Initialize Input System
    input = std::make_unique<Input>();

    // 6. Initialize math utils
    float randomSeed = (float)glfwGetTime();
    randomSeed += (float)clock();
    PMath::InitializeRandom(randomSeed);
    return true;
}

bool App::Run()
{
    if (!Init())
    {
        return false;
    }

    Loop();
    //TODO: Maybe shutdown function eventually
    return true;
}

void App::Loop()
{

    //CubeScene scene;
    TerrainScene scene;
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