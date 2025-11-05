#pragma once
#include <PRISM/Renderer/Mesh.h>
#include <PRISM/Renderer/Vertex.h>
#include <vector>
#include <glm/vec3.hpp>


/**
 * @class Plane
 * @brief A simple 2D plane mesh on the XZ plane centered at the origin.
 *
 * The Plane class inherits from Mesh and automatically generates a flat quad
 * with four vertices and two triangles. Each vertex contains position, color, UV, and normal.
 */
class Plane : public Mesh
{
public:
    Plane()
    {
        // Normal for the plane pointing up
        glm::vec3 normal = {0.0f, 1.0f, 0.0f};

        // Vertices (position, color, UV, normal)
        std::vector<Vertex> vertices = {
            {{-0.5f, 0.0f, -0.5f}, {0.0f,0.0f,0.0f,1.0f}, {0.0f, 0.0f}, normal}, // bottom-left
            {{ 0.5f, 0.0f, -0.5f}, {0.0f,0.0f,0.0f,1.0f}, {1.0f, 0.0f}, normal}, // bottom-right
            {{ 0.5f, 0.0f,  0.5f}, {0.0f,0.0f,0.0f,1.0f}, {1.0f, 1.0f}, normal}, // top-right
            {{-0.5f, 0.0f,  0.5f}, {0.0f,0.0f,0.0f,1.0f}, {0.0f, 1.0f}, normal}  // top-left
        };

        // Indices
        std::vector<unsigned int> indices = {
            0, 1, 2,
            2, 3, 0
        };

        Initialize(vertices, indices);
    }
};
