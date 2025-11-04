#include <PRISM/Editor/Panels/DevelopmentPanel.h>
#include <PRISM/Editor/Panels/EditorStatisticsPanel.h>
#include <PRISM/Editor/Panels/EditorScenePanel.h>
#include <imgui.h>

bool PRISM::Editor::DevelopmentPanel::toggleDisplay = true;

void PRISM::Editor::DevelopmentPanel::Display()
{
    if(!toggleDisplay)
        return;

    // Start our GUI here this will be a container for all other implementations we want,
    // e.g. Debug, Statistics, Scene Editor, etc.
    static bool initialized = false;
    static bool lightTheme = false;

    // Apply the light theme *once* on startup
    if (!initialized)
    {
        DarkTheme();
        initialized = true;
    }

    if (ImGui::Begin("PRISM Engine: Development GUI"))
    {
        // --- Development Options ---
        if (ImGui::CollapsingHeader("Development Options"))
        {
            if (ImGui::Checkbox("Light Theme", &lightTheme))
            {
                if (lightTheme)
                    LightTheme();
                else
                    DarkTheme();
            }
        }

        // Statistics GUI - FPS, Frame Time, etc.
        PRISM::Editor::EditorStatisticsPanel::Panel();

        // Debug GUI - Wireframe mode toggle, etc.
        if (ImGui::CollapsingHeader("Debug Options"))
        {
            static bool wireframe = false;
            if (ImGui::Checkbox("Wireframe Mode", &wireframe))
            {
                if (wireframe)
                {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                }
                else
                {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                }
            }
            // Add more debug options here as needed
        }

        // Scene Heirerarchy GUI
        PRISM::Editor::EditorScenePanel::Panel();
    }
    ImGui::End();
}

//CREDIT TO CHATGPT FOR THE THEME FUNCTIONS
void PRISM::Editor::DevelopmentPanel::LightTheme()
{
    ImGuiStyle &style = ImGui::GetStyle();
    ImVec4 *colors = style.Colors;

    // --- Core backgrounds ---
    colors[ImGuiCol_WindowBg] = ImVec4(0.97f, 0.97f, 0.98f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.98f, 0.98f, 0.99f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.98f);

    // --- Text ---
    colors[ImGuiCol_Text] = ImVec4(0.10f, 0.10f, 0.12f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.55f, 0.55f, 0.57f, 1.00f);

    // --- Headers / Tree nodes ---
    colors[ImGuiCol_Header] = ImVec4(0.74f, 0.82f, 0.94f, 0.55f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.70f, 0.80f, 0.98f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.65f, 0.75f, 0.95f, 1.00f);

    // --- Buttons ---
    colors[ImGuiCol_Button] = ImVec4(0.82f, 0.88f, 0.97f, 0.60f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.75f, 0.84f, 0.97f, 0.85f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.70f, 0.80f, 0.95f, 1.00f);

    // --- Frames (inputs, sliders, etc.) ---
    colors[ImGuiCol_FrameBg] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.92f, 0.95f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.85f, 0.90f, 0.96f, 1.00f);

    // --- Tabs ---
    colors[ImGuiCol_Tab] = ImVec4(0.92f, 0.94f, 0.97f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.75f, 0.83f, 0.96f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.70f, 0.78f, 0.92f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.94f, 0.95f, 0.97f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.90f, 0.92f, 0.96f, 1.00f);

    // --- Title bar ---
    colors[ImGuiCol_TitleBg] = ImVec4(0.92f, 0.93f, 0.96f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.80f, 0.85f, 0.95f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.96f, 0.97f, 0.99f, 1.00f);

    // --- Scrollbars ---
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.95f, 0.95f, 0.96f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.75f, 0.75f, 0.78f, 0.8f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.65f, 0.65f, 0.68f, 0.9f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.55f, 0.55f, 0.58f, 1.0f);

    // --- Checkmarks, sliders, etc. ---
    colors[ImGuiCol_CheckMark] = ImVec4(0.23f, 0.45f, 0.95f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.35f, 0.55f, 0.95f, 0.9f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.25f, 0.45f, 0.85f, 1.0f);

    // --- Borders & highlights ---
    colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.73f, 0.5f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.0f);

    // --- Style tweaks ---
    style.FrameBorderSize = 1.0f;
    style.WindowBorderSize = 1.0f;
    style.PopupBorderSize = 1.0f;

    style.WindowRounding = 8.0f;
    style.FrameRounding = 6.0f;
    style.GrabRounding = 6.0f;
    style.ScrollbarRounding = 8.0f;

    style.ItemSpacing = ImVec2(8, 6);
    style.WindowPadding = ImVec2(10, 10);
    style.FramePadding = ImVec2(6, 4);
}

//CREDIT TO CHATGPT FOR THE THEME FUNCTIONS
void PRISM::Editor::DevelopmentPanel::DarkTheme()
{
    ImGuiStyle &style = ImGui::GetStyle();
    ImVec4 *colors = style.Colors;

    // --- Core background colors ---
    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.11f, 0.13f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.12f, 0.12f, 0.14f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.10f, 0.94f);

    // --- Text ---
    colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.52f, 1.00f);

    // --- Headers (like collapsing nodes) ---
    colors[ImGuiCol_Header] = ImVec4(0.25f, 0.45f, 0.80f, 0.55f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.30f, 0.55f, 0.90f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.45f, 0.85f, 1.00f);

    // --- Buttons ---
    colors[ImGuiCol_Button] = ImVec4(0.25f, 0.45f, 0.80f, 0.55f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.55f, 0.90f, 0.80f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.45f, 0.85f, 1.00f);

    // --- Frames (input boxes, sliders, etc.) ---
    colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.17f, 0.19f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.20f, 0.22f, 0.25f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.28f, 0.32f, 1.00f);

    // --- Tabs ---
    colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.20f, 0.25f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.25f, 0.45f, 0.80f, 0.80f);
    colors[ImGuiCol_TabActive] = ImVec4(0.18f, 0.30f, 0.50f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.13f, 0.16f, 0.20f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.15f, 0.22f, 0.35f, 1.00f);

    // --- Title bars ---
    colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.10f, 0.12f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.20f, 0.20f, 0.25f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.08f, 0.08f, 0.10f, 1.00f);

    // --- Scrollbars ---
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.08f, 0.08f, 0.09f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.26f, 0.26f, 0.28f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.30f, 0.30f, 0.32f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.40f, 0.40f, 0.42f, 1.00f);

    // --- Borders ---
    colors[ImGuiCol_Border] = ImVec4(0.25f, 0.25f, 0.28f, 0.6f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.0f);

    // --- Style tweaks ---
    style.FrameBorderSize = 1.0f;
    style.WindowBorderSize = 1.0f;
    style.PopupBorderSize = 1.0f;

    style.WindowRounding = 8.0f;
    style.FrameRounding = 6.0f;
    style.GrabRounding = 6.0f;
    style.ScrollbarRounding = 8.0f;

    style.ItemSpacing = ImVec2(8, 6);
    style.WindowPadding = ImVec2(10, 10);
    style.FramePadding = ImVec2(6, 4);
}