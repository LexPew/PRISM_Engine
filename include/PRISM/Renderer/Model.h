#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include <PRISM/Renderer/Vertex.h>
// Holds model data, vertices and indices, etc
class Model
{
private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int VCO;
    unsigned int IBO;

protected:
    // World space
    glm::vec3 position{0, 0, 0};

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;


public:
    Model(const glm::vec3 &_position, const std::vector<Vertex> &_vertices, const std::vector<unsigned int> &_indices);
    ~Model();
    void Draw() const;

    std::vector<Vertex> &GetVertices() { return vertices; };
    std::vector<unsigned int> &GetIndices() { return indices; };

    void SetPosition(const glm::vec3& newPosition) {position = newPosition;};
    const glm::vec3& GetPosition() const { return position;};
};
