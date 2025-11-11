#include <PRISM/Examples/Panels/EditorSceneTerrainPanel.h>
#include <PRISM/Core/AssetManger.h>
#include <PRISM/Engine/SceneManager.h>
#include <PRISM/Examples/Scenes/TerrainScene.h>
#include <PRISM/Engine/Terrain.h>

#include <imgui.h>
// TODO: Make this more flexible
// TODO: Fix camera being removed
void PRISM::Editor::EditorSceneTerrainPanel::Panel()
{
    // This should only be called in the terrain scene but we will grab the scene and give some options like changing terrain
    std::shared_ptr<TerrainScene> scene = std::dynamic_pointer_cast<TerrainScene>(SceneManager::Get().GetScene());
    if (!scene)
        return;

    if (ImGui::CollapsingHeader("Terrain Options"))
    {
        static TerrainType currentType = TerrainType::PerlinNoise;
        ImGui::Text("Terrain Type:");
        ImGui::SameLine();
        ImGui::Text(currentType == TerrainType::PerlinNoise ? "Perlin Noise" : "Height Map");

        static int sizeX = 500;
        static int sizeZ = 500;
        ImGui::InputInt("Size X", &sizeX);
        ImGui::InputInt("Size Z", &sizeZ);

        if (ImGui::CollapsingHeader("Perlin Noise Settings"))
        {
            PerlinSettings &settings = scene->GetPerlinSettings();
            ImGui::SliderFloat("Noise Scale", &settings.noiseScale, 0.001f, 0.1f);
            ImGui::SliderInt("Octaves", &settings.octaves, 1, 10);
            ImGui::SliderFloat("Amplitude", &settings.amplitude, 1.0f, 500.0f);
        }

        if (ImGui::Button("Regenerate Terrain"))
        {
            scene->GenerateTerrain(TerrainType::PerlinNoise, sizeX, sizeZ);
        }

        if (ImGui::Button("Perlin Noise Terrain"))
        {
            scene->GenerateTerrain(TerrainType::PerlinNoise, sizeX  , sizeZ);
        }
        if (ImGui::Button("HeightMap 1 Noise Terrain"))
        {
            scene->SetHeightMapPath("examples/hmap.png");
            scene->GenerateTerrain(TerrainType::HeightMap, 400, 249);
        }
        if (ImGui::Button("HeightMap 2 Noise Terrain"))
        {
            scene->SetHeightMapPath("examples/custom_hmap.png");
            scene->GenerateTerrain(TerrainType::HeightMap, 300, 300);
        }
    }
}
