#include <PRISM/App.h>

//PRISM Includes
#include <PRISM/Utils/PMath.h>
#include <PRISM/Examples/CubeScene.h>
#include <PRISM/Examples/TerrainScene.h>

//ImGui Includes
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


//TODO:Remove scene stuff once done testing & cleanup
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


    // 6. Initialize math utils
    float randomSeed = (float)glfwGetTime();
    randomSeed += (float)clock();
    PMath::InitializeRandom(randomSeed);

    //Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplGlfw_InitForOpenGL(window.get()->GetGlfwWindow(), true);
    ImGui_ImplOpenGL3_Init();

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


        //ImGui New Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow();
        // Logic
        Input::Get().Update(window->GetGlfwWindow());
        scene.Update(deltaTime);

        scene.Draw();

        //ImGui Render
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        renderer->EndFrame();
        Input::Get().EndFrame();
    }

}