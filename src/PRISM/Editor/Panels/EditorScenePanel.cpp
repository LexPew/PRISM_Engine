#include <PRISM/Editor/Panels/EditorScenePanel.h>
#include <PRISM/Engine/SceneManager.h>
#include <imgui.h>
#include <string>

namespace PRISM::Editor
{
    void EditorScenePanel::Panel()
    {
        auto currentScene = SceneManager::Get().GetScene();
        if (!currentScene)
        {
            ImGui::TextDisabled("No active scene loaded.");
            return;
        }

        // === Outer Window Styling ===
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 12));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 8));
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.97f, 0.97f, 0.99f, 0.75f));
       

        if (ImGui::CollapsingHeader("Scene Information", ImGuiTreeNodeFlags_DefaultOpen))
        {
            //Active Scene
            ImGui::SeparatorText("Active Scene");
            ImGui::Spacing();

     
            ImGui::TextColored(ImVec4(0.30f, 0.55f, 1.0f, 1.0f),
                               "%p", currentScene.get());
            ImGui::Spacing();
            ImGui::Separator();

            //Scene Light Settings
            ImGui::SeparatorText("Scene Light Settings");
            ImGui::Spacing();
            auto& lightSettings = currentScene->GetSceneLighting();
            ImGui::ColorEdit3("Ambient Colour", &lightSettings.ambientLightColour.x);
            ImGui::Spacing();
            ImGui::DragFloat3("Directional Light", &lightSettings.directionalLight.direction.x,.1f);
            ImGui::Separator();

            static bool showHierarchy = false;
            ImGui::Checkbox("Show Scene Hierarchy", &showHierarchy);

            if (showHierarchy)
            {
                ImGui::Begin("SceneHierarchyPanel", nullptr);

                auto& entities = currentScene->GetAllEntities();
                ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.45f, 1.0f), "Entities: %zu", entities.size());
                ImGui::Separator();

                static int selectedIndex = -1;

                for (size_t i = 0; i < entities.size(); ++i)
                {
                    auto& entity = entities[i];
                    const std::string label = "Entity " + std::to_string(i);

                    ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_OpenOnArrow |
                                                   ImGuiTreeNodeFlags_SpanAvailWidth;
                    if (selectedIndex == static_cast<int>(i))
                        nodeFlags |= ImGuiTreeNodeFlags_Selected;

                    bool opened = ImGui::TreeNodeEx((void*)(intptr_t)i, nodeFlags, "%s", label.c_str());

                    // Hover highlight effect
                    if (ImGui::IsItemHovered() && selectedIndex != static_cast<int>(i))
                    {
                        ImDrawList* drawList = ImGui::GetWindowDrawList();
                        ImVec2 min = ImGui::GetItemRectMin();
                        ImVec2 max = ImGui::GetItemRectMax();
                        drawList->AddRectFilled(min, max, IM_COL32(210, 220, 255, 60), 6.0f);
                    }

                    if (ImGui::IsItemClicked())
                        selectedIndex = static_cast<int>(i);

                    if (opened)
                    {
                        ImGui::PushID(static_cast<int>(i));
                        ImGui::Indent();

                        // === Fancy Transform Section ===
                        ImGui::SeparatorText("Transform");

                        auto& tr = entity->transform;
                        ImGui::Spacing();

                        ImGui::PushItemWidth(-10);

                        ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "Position");
                        ImGui::SameLine();
                        ImGui::DragFloat3("##pos", &tr.position.x, 0.1f);

                        ImGui::TextColored(ImVec4(0.3f, 1.0f, 0.3f, 1.0f), "Rotation");
                        ImGui::SameLine();
                        ImGui::DragFloat3("##rot", &tr.rotation.x, 0.1f);

                        ImGui::TextColored(ImVec4(0.3f, 0.5f, 1.0f, 1.0f), "Scale");
                        ImGui::SameLine();
                        ImGui::DragFloat3("##scl", &tr.scale.x, 0.1f);

                        ImGui::PopItemWidth();
                        ImGui::Unindent();
                        ImGui::PopID();
                        ImGui::TreePop();
                    }
                }

                ImGui::End();
            }
        }

        // === Cleanup ===
        ImGui::PopStyleColor(1);
        ImGui::PopStyleVar(3);
    }
}
