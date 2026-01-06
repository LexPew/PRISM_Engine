#include <PRISM/Examples/Scenes/TerrainScene.h>
#include <PRISM/Engine/Terrain.h>
#include <PRISM/Engine/OrbitalCameraEntity.h>
#include <PRISM/Examples/Panels/EditorSceneTerrainPanel.h>
#include <algorithm>

void TerrainScene::ResetCameraPosition(int xSize, int zSize)
{
    if (!camera) return;
    auto &camXform = camera->GetLocalTransform();
    camXform.position = { 0.0f, 250.0f, zSize / 2.0f };
    camXform.LookAt({ 0.0f, 0.0f, 0.0f });
}

void TerrainScene::Start()
{
    sceneLighting.directionalLight.direction = glm::vec3(0.0f, 1.0f, 3.1f);

    // Camera is a root-level entity owned by the scene
    {
        EmplaceEntity(std::make_unique<OrbitalCameraEntity>());
    }

    // Generate a default terrain and point the camera at it
    GenerateTerrain(TerrainType::PerlinNoise, 1500, 1500);
    ResetCameraPosition(1500, 1500);
}

void TerrainScene::Panel()
{
    PRISM::Editor::EditorSceneTerrainPanel::Panel();
}

void TerrainScene::Clear()
{
    //Remove all entities and add back the camera
    entities.clear();
    EmplaceEntity(std::make_unique<OrbitalCameraEntity>());
}

void TerrainScene::GenerateTerrain(TerrainType type, int sizeX, int sizeZ)
{
    Clear();

    // Environment root holds terrain (and could hold lights if needed)
    auto environmentRoot = std::make_unique<Entity>();

    switch (type)
    {
    case TerrainType::PerlinNoise:
    {
        auto perlin = std::make_unique<Terrain>(sizeX, sizeZ, perlinSettings.noiseScale, perlinSettings.octaves, perlinSettings.amplitude);
        perlin->GetLocalTransform().position = { -sizeX / 2.0f, 0.0f, -sizeZ / 2.0f };
        environmentRoot->AddChild(std::move(perlin));
        break;
    }
    case TerrainType::HeightMap:
    {
        auto heightMap = std::make_unique<Terrain>(sizeX, sizeZ, FLoader::LoadImage(FLoader::GetAssetPath(heightMapPath)));
        heightMap->GetLocalTransform().position = { -sizeX / 2.0f, 0.0f, -sizeZ / 2.0f };
        environmentRoot->AddChild(std::move(heightMap));
        break;
    }
    default:
        break;
    }

    // Add environment to scene
    EmplaceEntity(std::move(environmentRoot));

    // Reposition camera for the new terrain
    ResetCameraPosition(sizeX, sizeZ);
}
