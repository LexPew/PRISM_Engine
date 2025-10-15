#pragma once
#include <PRISM/Renderer/Mesh.h>
static std::vector<Vertex> cubeVerts = {
    {{0, 0, 0}, {1, 0, 0, 1}},   // red
    {{1, 0, 0}, {0, 1, 0, 1}},   // green
    {{0, 1, 0}, {0, 0, 1, 1}},   // blue
    {{1, 1, 0}, {1, 1, 0, 1}},   // yellow
    {{0, 0, -1}, {1, 0, 1, 1}},  // magenta
    {{1, 0, -1}, {0, 1, 1, 1}},  // cyan
    {{0, 1, -1}, {1, 1, 1, 1}},  // white
    {{1, 1, -1}, {0.2f, 0.5f, 1.0f, 1}} // light blue
};


static std::vector<unsigned int> cubeIndices = {
    // Front
    0, 1, 2, 2, 3, 1,
    // Back
    4, 5, 7, 7, 6, 4,
    // Right
    1, 3, 5, 5, 3, 7,
    // Left
    0, 4, 6, 6, 2, 0,
    // Top
    2, 6, 3, 3, 6, 7,
    // Bottom
    1, 0, 4, 4, 5, 1};
class Cube : public Mesh
{
public:
    Cube() : Mesh(cubeVerts, cubeIndices) {};
};