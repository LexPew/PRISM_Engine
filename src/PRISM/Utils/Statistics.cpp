#include <PRISM/Utils/Statistics.h>
#include <imgui.h>
void Statistics::GUI()
{
    if (ImGui::Begin("Stats"))
    {
        float fps = 1.0f / Time::deltaTime;
        ImGui::Text("FPS: %.0f", fps);
    }
    ImGui::End();
}