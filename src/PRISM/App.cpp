#include <PRISM/App.h>

// PRISM Includes
#include <PRISM/Utils/PMath.h>
#include <PRISM/Examples/CubeScene.h>
#include <PRISM/Core/Input/Input.h>
#include <PRISM/Engine/SceneManager.h>
#include <PRISM/Core/Time.h>
#include <PRISM/Utils/FLoader.h>

#include <PRISM/Renderer/Renderer.h>
#include <PRISM/Editor/Panels/DevelopmentPanel.h>
// ImGui Includes
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <ImGuizmo.h>


bool App::Init()
{
    // Initialize Everything

    // 1. Create the window first
    window = std::make_shared<Window>(screenWidth, screenHeight, " /|/ P.R.I.S.M //");

    // 2. Load GL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return false;
    }

    // 3. Initialize Renderer
    Renderer::Get();

    // 6. Initialize math utils
    float randomSeed = (float)glfwGetTime();
    randomSeed += (float)clock();
    PMath::InitializeRandom(randomSeed);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplGlfw_InitForOpenGL(window->GetGlfwWindow(), true);
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

    ShutDown();
    return true;
}

void App::Loop()
{
    SceneManager::Get().SetScene(std::make_shared<CubeScene>());
    SceneManager::Get().Start();

    while (!window->ShouldClose())
    {
        Time::Update();
        // Rendering

        Renderer::Get().BeginFrame();

        // ImGui New Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGuizmo::BeginFrame();

        if (Input::Get().IsKeyPressed(GLFW_KEY_F1))
        {
            PRISM::Editor::DevelopmentPanel::ToggleDisplay();
        }
        PRISM::Editor::DevelopmentPanel::Display();

        // Logic
        Input::Get().Update(window->GetGlfwWindow());
        SceneManager::Get().Update(Time::deltaTime);

        SceneManager::Get().Draw();

        // ImGui Render
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        Renderer::Get().EndFrame();
        Input::Get().EndFrame();
    }
}
void App::ShutDown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    SceneManager::Get().ShutDown();
    Renderer::Get().ShutDown();
}