#pragma once
#include <PRISM/Renderer/Mesh.h>
#include <PRISM/Renderer/Vertex.h>
#include <vector>
#include <glm/vec3.hpp>

/**
 * @class Cube
 * @brief A Mesh representing a single cube
 *
 * Inherits from Mesh and automatically generates vertices and indices for
 * all six colored faces of the cube. Each face has its own color and UVs.
 */
class RubiksCubeExample : public Mesh
{
public:
    /**
     * @brief Constructs a Cube block mesh
     *
     * Generates vertices and indices for a unit cube aligned to the origin
     * and initializes the Mesh base class with this data.
     */
    RubiksCubeExample()
    {
        // Vertices for the cube (position, color, UV)
 std::vector<Vertex> vertices = {
            // Top Face (white) - normal (0,1,0)
            {{0,1,0},   {1,1,1,1}, {0,1}, {0,1,0}},   
            {{1,1,0},   {1,1,1,1}, {1,1}, {0,1,0}},   
            {{0,1,-1},  {1,1,1,1}, {0,0}, {0,1,0}},   
            {{1,1,-1},  {1,1,1,1}, {1,0}, {0,1,0}},

            // Bottom Face (yellow) - normal (0,-1,0)
            {{0,0,0},   {1,1,0,1}, {0,0}, {0,-1,0}},
            {{1,0,0},   {1,1,0,1}, {1,0}, {0,-1,0}},
            {{0,0,-1},  {1,1,0,1}, {0,1}, {0,-1,0}},
            {{1,0,-1},  {1,1,0,1}, {1,1}, {0,-1,0}},

            // Left Face (blue) - normal (-1,0,0)
            {{0,0,0},   {0,0,1,1}, {1,0}, {-1,0,0}},
            {{0,1,0},   {0,0,1,1}, {1,1}, {-1,0,0}},
            {{0,0,-1},  {0,0,1,1}, {0,0}, {-1,0,0}},
            {{0,1,-1},  {0,0,1,1}, {0,1}, {-1,0,0}},

            // Right Face (red) - normal (1,0,0)
            {{1,0,0},   {1,0,0,1}, {0,0}, {1,0,0}},
            {{1,1,0},   {1,0,0,1}, {0,1}, {1,0,0}},
            {{1,0,-1},  {1,0,0,1}, {1,0}, {1,0,0}},
            {{1,1,-1},  {1,0,0,1}, {1,1}, {1,0,0}},

            // Front Face (green) - normal (0,0,1)
            {{0,0,0},   {0,1,0,1}, {0,0}, {0,0,1}},
            {{1,0,0},   {0,1,0,1}, {1,0}, {0,0,1}},
            {{0,1,0},   {0,1,0,1}, {0,1}, {0,0,1}},
            {{1,1,0},   {0,1,0,1}, {1,1}, {0,0,1}},

            // Back Face (orange) - normal (0,0,-1)
            {{0,0,-1},  {1,0.5f,0,1}, {1,0}, {0,0,-1}},
            {{1,0,-1},  {1,0.5f,0,1}, {0,0}, {0,0,-1}},
            {{0,1,-1},  {1,0.5f,0,1}, {1,1}, {0,0,-1}},
            {{1,1,-1},  {1,0.5f,0,1}, {0,1}, {0,0,-1}}
        };

        // Indices for the cube faces
        std::vector<unsigned int> indices = {
            0, 1, 2,   2, 1, 3,      // Top Face
            4, 5, 6,   6, 5, 7,      // Bottom Face
            8, 9, 10,  10, 9, 11,    // Left Face
            12, 13, 14, 14, 13, 15,  // Right Face
            16, 17, 18, 18, 17, 19,  // Front Face
            20, 21, 22, 22, 21, 23   // Back Face
        };

        // Initialize the Mesh with the vertices and indices
        Initialize(vertices, indices);
    }
};
