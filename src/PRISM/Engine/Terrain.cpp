#include <PRISM/Engine/Terrain.h>

#include <glm/vec3.hpp>

#include <PRISM/Utils/PMath.h>
#include <fmt/core.h>

#include <cmath>
#include <Siv/PerlinNoise.hpp>

#include <PRISM/Core/Time.h>
// TODO: Cleanup and move variables to header such as height scale etc
void Terrain::GenerateFromHeightMap(const ImageData &heightMap)
{
    // Check whether we must perform minification or magnification from the already loaded imagedata heightMap

    std::vector<unsigned int> indices;
    // Loop through and generate vertices one unit apart
    for (int x = 0; x < gridSizeX; x++)
    {
        for (int z = 0; z < gridSizeZ; z++)
        {
            // We use normalized coordinates here so that if the heightmap is larger or smaller we sample accordingly
            glm::vec2 vertexPositionNormalized = glm::vec2((float)x / (float)(gridSizeX), (float)z / (float)(gridSizeZ));

            // Grab the relative position in the heightmap
            int heightMapSamplePointX = vertexPositionNormalized.x * (float)heightMap.width;
            int heightMapSamplePointY = vertexPositionNormalized.y * (float)heightMap.height;

            // Then we get the index inside the flattened image array, since its row first array we use sampleY * arrayWidth + sampleX
            // Multiplied by 4 as there are 4 channels rgba
            int index = (heightMapSamplePointY * heightMap.width + heightMapSamplePointX) * 4;

            // Next we just use on color channel since its grayscale as our heightvalue

            unsigned char heightValue = heightMap.data[index]; // Red channel
            // This gives us a value between 0-255 so we need to scale it down via normalizing and then multiply by the max scale
            float maxHeightScale = 25.0f;                  // 50 units high max
            float normalizedHeight = heightValue / 255.0f; // 0-1
            normalizedHeight *= maxHeightScale;
            // We use 0-1 range so divide heightvalue by 255 to get this
            float greyScaleCol = heightValue / 255.0f;
            glm::vec4 color = glm::vec4(greyScaleCol, greyScaleCol, greyScaleCol, 1.0f);
            //TODO: ADD UV
            vertices.push_back({{x, normalizedHeight, z}, color,{0,0}});
        }
    }

    GenerateIndices(indices);


    auto terrainMesh = std::make_shared<Mesh>(vertices,indices);
    SetMesh(terrainMesh);
}

void Terrain::GenerateFromPerlinNoise(float scale, int octaves)
{
    //Set perlin noise seed
    siv::PerlinNoise::seed_type seed = (unsigned int)Time::elapsedTime;

    siv::PerlinNoise perlin{seed};

    std::vector<unsigned int> indices;
    // Loop through and generate vertices one unit apart
    for (int x = 0; x < gridSizeX; x++)
    {
        for (int z = 0; z < gridSizeZ; z++)
        {
            //Get the perlin noise for this position and use it for the height
            const float noise = perlin.octave2D_01((x*scale), (z*scale), octaves);

            //Normalized
            float normalizedHeight = maxScale * noise;
            float greyScaleCol = (noise + 1) / 2;

            glm::vec4 color = glm::vec4(greyScaleCol, greyScaleCol, greyScaleCol, 1.0f);
            //TODO: ADD UV
            vertices.push_back({{x, normalizedHeight, z}, color, {0,0}});
        }
    }

    GenerateIndices(indices);
    auto terrainMesh = std::make_shared<Mesh>(vertices,indices);
    SetMesh(terrainMesh);
}
void Terrain::GenerateIndices(std::vector<unsigned int> &indices)
{
    for (int x = 0; x < gridSizeX - 1; x++)
    {
        for (int z = 0; z < gridSizeZ - 1; z++)
        {
            unsigned int topLeft = x * gridSizeZ + z;
            unsigned int topRight = x * gridSizeZ + (z + 1);
            unsigned int bottomLeft = (x + 1) * gridSizeZ + z;
            unsigned int bottomRight = (x + 1) * gridSizeZ + (z + 1);

            // Flip based on both row and column (checkerboard pattern)
            bool flip = ((x + z) % 2 == 0);

            if (flip)
            {
                // Diagonal:
                indices.push_back(topLeft);
                indices.push_back(topRight);
                indices.push_back(bottomLeft);

                indices.push_back(bottomLeft);
                indices.push_back(topRight);
                indices.push_back(bottomRight);
            }
            else
            {
                // Diagonal: /
                indices.push_back(topLeft);
                indices.push_back(bottomRight);
                indices.push_back(bottomLeft);

                indices.push_back(topLeft);
                indices.push_back(topRight);
                indices.push_back(bottomRight);
            }
        }
    }
}
