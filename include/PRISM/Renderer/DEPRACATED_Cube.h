#pragma once
#include <PRISM/Renderer/Mesh.h>
#include <PRISM/Renderer/Vertex.h>
#include <vector>
#include <glm/vec3.hpp>

/**
 * @class Cube
 * @brief A simple cube mesh with per-face normals, colors, and UVs.
 */
class Depracated_Cube : public Mesh
{
public:
    Depracated_Cube()
    {
        // Vertices (position, color, UV, normal)
        std::vector<Vertex> vertices = {
            // Front Face (red) - normal (0,0,1)
            {{0,0,0}, {1,0,0,1}, {0,0}, {0,0,1}},
            {{1,0,0}, {0,1,0,1}, {1,0}, {0,0,1}},
            {{0,1,0}, {0,0,1,1}, {0,1}, {0,0,1}},
            {{1,1,0}, {1,1,0,1}, {1,1}, {0,0,1}},

            // Back Face (magenta) - normal (0,0,-1)
            {{0,0,-1}, {1,0,1,1}, {0,0}, {0,0,-1}},
            {{1,0,-1}, {0,1,1,1}, {1,0}, {0,0,-1}},
            {{0,1,-1}, {1,1,1,1}, {0,1}, {0,0,-1}},
            {{1,1,-1}, {0.2f,0.5f,1.0f,1}, {1,1}, {0,0,-1}}
        };

        // Indices
        std::vector<unsigned int> indices = {
            // Front
            0, 1, 2, 2, 1, 3,
            // Back
            4, 5, 6, 6, 5, 7,
            // Right
            1, 3, 5, 5, 3, 7,
            // Left
            0, 2, 4, 4, 2, 6,
            // Top
            2, 3, 6, 6, 3, 7,
            // Bottom
            0, 1, 4, 4, 1, 5
        };

        // Initialize the mesh
        Initialize(vertices, indices);
    }
};
