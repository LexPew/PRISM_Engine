#include <PRISM/Editor/Panels/EditorStatisticsPanel.h>
#include <imgui.h>

void PRISM::Editor::EditorStatisticsPanel::Panel()
{
    if (ImGui::CollapsingHeader("Statistics"))
    {
        float fps = 1.0f / Time::deltaTime;
        float frameTime = Time::deltaTime * 1000.0f; // in ms
        ImGui::Text("FPS: %.0f", fps);
        ImGui::Text("Frame Time: %.2f ms", frameTime);
    }
}
