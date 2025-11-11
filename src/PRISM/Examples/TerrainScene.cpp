#include <PRISM/Examples/Scenes/TerrainScene.h>
#include <PRISM/Engine/Terrain.h>

#include <PRISM/Examples/Panels/EditorSceneTerrainPanel.h>

 void TerrainScene::ResetCameraPosition(int xSize, int zSize)
{
    //float yPos = static_cast<float>(std::max(xSize, zSize)) / 2.0f;
    camera->transform.position = { 0, 250, zSize / 2.0f };
    camera->transform.LookAt({ 0, 0, 0 });
}

void TerrainScene::Start()
{
    camera = std::make_shared<OrbitalCameraEntity>();
    AddEntity(camera);
    //Generate a default terrain and point the camera at it
    GenerateTerrain(TerrainType::PerlinNoise, 500, 500);
    //Calculate camera position based on terrain size and angle we want to view it from.
    ResetCameraPosition(500, 500);
    
}

void TerrainScene::Panel()
{
    PRISM::Editor::EditorSceneTerrainPanel::Panel();
}

void TerrainScene::Clear()
{
    entities.clear();
    AddEntity(camera);
}

void TerrainScene::GenerateTerrain(TerrainType type, int sizeX, int sizeZ)
{
    Clear();
    switch (type)
    {
    case TerrainType::PerlinNoise:
    {
        auto perlin = std::make_shared<Terrain>(sizeX, sizeZ, perlinSettings.noiseScale, perlinSettings.octaves, perlinSettings.amplitude);
        perlin->transform.position = {-sizeX / 2.0f, 0.0f,- sizeZ / 2.0f};
        AddEntity(perlin);
        break;
    }
    case TerrainType::HeightMap:
    {
        auto heightMap = std::make_shared<Terrain>(sizeX, sizeZ, FLoader::LoadImage(FLoader::GetAssetPath(heightMapPath)));
        heightMap->transform.position = { -sizeX / 2.0f, 0.0f, -sizeZ / 2.0f };
        AddEntity(heightMap);
        break;
    }
    ResetCameraPosition(sizeX, sizeZ);
    };
}
