#include <PRISM/Examples/Panels/EditorSceneTerrainPanel.h>
#include <PRISM/Core/AssetManger.h>
#include <PRISM/Engine/SceneManager.h>
#include <PRISM/Engine/Terrain.h>

#include <imgui.h>
void Clear()
{
    auto currentScene = SceneManager::Get().GetScene();
    currentScene->GetEntities().clear();
}

// TODO: Make this more flexible 
//TODO: Fix camera being removed
void PRISM::Editor::EditorSceneTerrainPanel::Panel()
{
    // This should only be called in the terrain scene but we will grab the scene and give some options like changing terrain
    auto currentScene = SceneManager::Get().GetScene();

    if (ImGui::CollapsingHeader("Terrain Options"))
    {
        std::shared_ptr<Terrain> gen;
        if (ImGui::Button("Perlin Noise Terrain"))
        {
            Clear();
            gen = std::make_shared<Terrain>(500, 500, 0.01f, 4);
            currentScene->AddEntity(gen);
        }
        if (ImGui::Button("HeightMap 1 Noise Terrain"))
        {
            Clear();
            gen = std::make_shared<Terrain>(400, 249, FLoader::LoadImage(FLoader::GetAssetPath("examples/hmap.png")));

            currentScene->AddEntity(gen);
        }
        if (ImGui::Button("HeightMap 2 Noise Terrain"))
        {
            Clear();
            gen = std::make_shared<Terrain>(400, 249, FLoader::LoadImage(FLoader::GetAssetPath("examples/custom_hmap.png")));
            currentScene->AddEntity(gen);
        }

    }
}