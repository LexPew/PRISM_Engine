#pragma once

#include <PRISM/Engine/Scene.h>

#include <PRISM/Engine/OrbitalCameraEntity.h>
#include <PRISM/Utils/FLoader.h>

enum class TerrainType
{
    PerlinNoise,
    HeightMap
};

struct PerlinSettings
{
    float noiseScale{0.01f};
    int octaves{4};
    float amplitude{1.0f};
};

class TerrainScene : public Scene
{
private:
    std::shared_ptr<OrbitalCameraEntity> camera;

    PerlinSettings perlinSettings; 

    std::string heightMapPath{"examples/hmap.png"}; // Default height map path

    void ResetCameraPosition(int xSize, int zSize);
public:
    TerrainScene() = default;

    void Start() override;

    void Panel() override;

    // TODO: Consider moving the Clear function to the base Scene class if entity clearing is needed in multiple scenes.

    void Clear();

    void GenerateTerrain(TerrainType type, int sizeX, int sizeZ);

    PerlinSettings& GetPerlinSettings() { return perlinSettings; }
    void SetHeightMapPath(const std::string& path) { heightMapPath = path; }
};