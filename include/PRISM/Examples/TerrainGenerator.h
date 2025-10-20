#pragma once

#include <PRISM/Engine/ModelEntity.h>
#include <PRISM/Renderer/Vertex.h>
//TODO: Update to sample height maps
class TerrainGenerator: public ModelEntity
{
    int gridSizeX{16};
    int gridSizeZ{16};

    std::vector<Vertex> vertices;
public:
    TerrainGenerator(int p_gridSizeX, int p_gridSizeZ)
     {
        gridSizeX = p_gridSizeX;
        gridSizeZ = p_gridSizeZ;
        GenerateTerrainVertices();
    };

    void GenerateTerrainVertices();
private:
};