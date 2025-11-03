#pragma once

#include <PRISM/Engine/ModelEntity.h>
#include <PRISM/Renderer/Vertex.h>
#include <PRISM/Utils/FLoader.h>
// TODO: Update to sample height maps
class Terrain : public ModelEntity
{
private:
    int gridSizeX{16};
    int gridSizeZ{16};

    float maxScale{50.0f};

    std::vector<Vertex> vertices;

public:
    Terrain(int p_gridSizeX, int p_gridSizeZ, const ImageData& p_heightMap) : gridSizeX(p_gridSizeX), gridSizeZ(p_gridSizeZ)
    {
        GenerateFromHeightMap(p_heightMap);
    };
    Terrain(int p_gridSizeX, int p_gridSizeZ, float p_scale, int p_octaves) : gridSizeX(p_gridSizeX), gridSizeZ(p_gridSizeZ)
    {
        GenerateFromPerlinNoise(p_scale, p_octaves);
    };

private:
    void GenerateFromHeightMap(const ImageData &heightMap);
    void GenerateFromPerlinNoise( float scale, int octaves);
    void GenerateIndices(std::vector<unsigned int> &indices);
};