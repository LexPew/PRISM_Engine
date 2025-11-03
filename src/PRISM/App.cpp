#include <PRISM/App.h>

//PRISM Includes
#include <PRISM/Utils/PMath.h>
#include <PRISM/Examples/CubeScene.h>
#include <PRISM/Examples/TerrainScene.h>
#include <PRISM/Core/Input/Input.h>
#include <PRISM/Engine/SceneManager.h>
#include <PRISM/Core/Time.h>
#include <PRISM/Utils/Debug.h>
#include <PRISM/Utils/FLoader.h>
//ImGui Includes
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


//TODO:Remove scene stuff once done testing & cleanup
bool App::Init()
{
    // Initialize Everything

    // 1. Create the window first
    window = std::make_shared<Window>(screenWidth, screenHeight, " /|/ P.R.I.S.M //");

    // 2. Load GL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        // TODO: Add Error Printing
        // fmt::println("Failed to load GLAD");
        return false;
    }

    // 3. Initialize Renderer
    Renderer::Get();


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


    //SceneManager::Get().SetScene(std::make_shared<TerrainScene>());
    SceneManager::Get().SetScene(std::make_shared<CubeScene>());
    SceneManager::Get().Start();

    while (!window->ShouldClose())
    {
        Time::Update();
        // Rendering

        Renderer::Get().BeginFrame();

        //ImGui New Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        //Statistics::GUI();
        //ImGui::ShowDemoWindow();a
        Debug::GUI();
        SceneManager::Get().GetScene()->GUI();
        // Logic
        Input::Get().Update(window->GetGlfwWindow());
        SceneManager::Get().Update(Time::deltaTime);

        SceneManager::Get().Draw();

        //ImGui Render
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        Renderer::Get().EndFrame();
        Input::Get().EndFrame();
    }

}