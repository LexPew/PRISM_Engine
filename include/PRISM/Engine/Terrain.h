#pragma once

#include <PRISM/Engine/ModelEntity.h>
#include <PRISM/Renderer/Vertex.h>
#include <PRISM/Utils/FLoader.h>
#include <future>
struct TerrainData {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};
// TODO: Update to sample height maps
class Terrain : public ModelEntity
{
private:
    int gridSizeX{16};
    int gridSizeZ{16};

    bool isGenerating{false};
    std::future<TerrainData> terrainFuture;


    std::vector<Vertex> vertices;

    TerrainData GenerateFromHeightMapAsync(const ImageData &heightMap);
    TerrainData GenerateFromPerlinNoiseAsync(float scale, int octaves, float amplitude);
public:
    Terrain(int p_gridSizeX, int p_gridSizeZ, const ImageData& p_heightMap) : gridSizeX(p_gridSizeX), gridSizeZ(p_gridSizeZ)
    {
        SetMesh(nullptr);
        GenerateFromHeightMap(p_heightMap);
    };
    Terrain(int p_gridSizeX, int p_gridSizeZ, float p_scale, int p_octaves, float p_amplitude) : gridSizeX(p_gridSizeX), gridSizeZ(p_gridSizeZ)
    {
        SetMesh(nullptr);
        GenerateFromPerlinNoise(p_scale, p_octaves, p_amplitude);
    };

    void Update(float deltaTime) override;
private:
    void GenerateFromHeightMap(const ImageData &heightMap);
    void GenerateFromPerlinNoise( float scale, int octaves, float amplitude);
    void GenerateIndices(std::vector<unsigned int> &indices);
};