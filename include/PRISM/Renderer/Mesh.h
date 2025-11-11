#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include <PRISM/Renderer/Vertex.h>
// Holds model data, vertices and indices, etc
class Mesh
{
private:
    unsigned int VAO{0}; //Object
    unsigned int VBO{0}; //Vertices
    unsigned int IBO{0}; //Indices

protected:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

public:
    Mesh() {};
    Mesh(const std::vector<Vertex> &_vertices, const std::vector<unsigned int> &_indices);
    ~Mesh();



    void Initialize(const std::vector<Vertex> &_vertices, const std::vector<unsigned int> &_indices);
    void Draw() const;

    std::vector<Vertex> &GetVertices() { return vertices; };
    std::vector<unsigned int> &GetIndices() { return indices; };

    //Helper Functions

    void CalculateNormals();
};
