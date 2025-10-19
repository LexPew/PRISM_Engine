#pragma once
#include <PRISM/Renderer/Mesh.h>

 static std::vector<Vertex> rubixVerts{
    // Top Face (white)
    {{0,1,0},   {1,1,1,1}},   // Bottom left
    {{1,1,0},   {1,1,1,1}},   // Bottom right
    {{0,1,-1},  {1,1,1,1}},   // Top left
    {{1,1,-1},  {1,1,1,1}},   // Top right

    // Bottom Face (yellow)
    {{0,0,0},   {1,1,0,1}},   // Bottom left
    {{1,0,0},   {1,1,0,1}},   // Bottom right
    {{0,0,-1},  {1,1,0,1}},   // Top left
    {{1,0,-1},  {1,1,0,1}},   // Top right

    // Left Face (blue)
    {{0,0,0},   {0,0,1,1}},   // Bottom left
    {{0,1,0},   {0,0,1,1}},   // Top left
    {{0,0,-1},  {0,0,1,1}},   // Bottom right
    {{0,1,-1},  {0,0,1,1}},   // Top right

    // Right Face (red)
    {{1,0,0},   {1,0,0,1}},   // Bottom left
    {{1,1,0},   {1,0,0,1}},   // Top left
    {{1,0,-1},  {1,0,0,1}},   // Bottom right
    {{1,1,-1},  {1,0,0,1}},   // Top right

    // Front Face (green)
    {{0,0,0},   {0,1,0,1}},   // Bottom left
    {{1,0,0},   {0,1,0,1}},   // Bottom right
    {{0,1,0},   {0,1,0,1}},   // Top left
    {{1,1,0},   {0,1,0,1}},   // Top right

    // Back Face (orange)
    {{0,0,-1},  {1,0.5f,0,1}}, // Bottom left
    {{1,0,-1},  {1,0.5f,0,1}}, // Bottom right
    {{0,1,-1},  {1,0.5f,0,1}}, // Top left
    {{1,1,-1},  {1,0.5f,0,1}}  // Top right
};

static std::vector<unsigned int> rubixIndices {
    // Top Face (verts 0–3)
    0, 1, 2,   2, 1, 3,

    // Bottom Face (verts 4–7)
    4, 5, 6,   6, 5, 7,

    // Left Face (verts 8–11)
    8, 9, 10,  10, 9, 11,

    // Right Face (verts 12–15)
    12, 13, 14,  14, 13, 15,

    // Front Face (verts 16–19)
    16, 17, 18,  18, 17, 19,

    // Back Face (verts 20–23)
    20, 21, 22,  22, 21, 23
};

class RubiksCubeExample : public Mesh
{
private:


public:

    RubiksCubeExample() : Mesh(rubixVerts, rubixIndices) {};
};
