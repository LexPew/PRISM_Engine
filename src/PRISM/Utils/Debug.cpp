#include <PRISM/Utils/Debug.h>
#include <PRISM/Utils/Statistics.h>

#include <imgui.h>
void Debug::GUI()
{
    Statistics::GUI();
    static bool wireframe = false;
    if (ImGui::Begin("Debug"))
    {
        ImGui::Checkbox("Wireframe", &wireframe); // Add logic here if needed in the future
    }
    ImGui::End();
    
    if (wireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}