#include <PRISM/Examples/TerrainGenerator.h>
#include <glm/vec3.hpp>

#include <PRISM/Utils/PMath.h>

//TODO: Cleanup and move variables to header such as height scale etc
void TerrainGenerator::GenerateTerrainVertices()
{
    

    std::vector<unsigned int> indices;
    // Loop through and generate vertices one unit apart
    for (int x = 0; x < gridSizeX; x++)
    {
        for (int z = 0; z < gridSizeZ; z++)
        {
            // Go through a row and all its columns
            // So X * columns (gridSizeZ) + z = triangle index;
            float maxHeight = 2.0f;
            float randomHeight = PMath::RandomRange(0.0f, maxHeight);
            float colourScale = randomHeight / maxHeight;
            glm::vec4 color = {0,.8f,.2f,1.0f};
            color *=  colourScale;
            color.a = 1.0f;
            vertices.push_back({{x, randomHeight, z}, color});
        }
    }

    for (int x = 0; x < gridSizeX - 1; x++)
    {
        for (int z = 0; z < gridSizeZ - 1; z++)
        {
            unsigned int topLeft = x * gridSizeZ + z;
            unsigned int topRight = x * gridSizeZ + (z + 1);
            unsigned int bottomLeft = (x + 1) * gridSizeZ + z;
            unsigned int bottomRight = (x + 1) * gridSizeZ + (z + 1);

            indices.push_back(bottomLeft);
            indices.push_back(topLeft);
            indices.push_back(topRight);
            indices.push_back(topRight);
            indices.push_back(bottomRight);
            indices.push_back(bottomLeft);
        }
    }
    static Mesh mesh(vertices, indices);
    SetMesh(mesh);
}