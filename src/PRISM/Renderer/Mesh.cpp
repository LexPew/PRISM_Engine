#include <PRISM/Renderer/Mesh.h>
#include <glad/glad.h>
#include <cmath>

Mesh::Mesh(const std::vector<Vertex> &_vertices, const std::vector<unsigned int> &_indices)
{
    Initialize(_vertices, _indices);
}

Mesh::~Mesh()
{
    // Emsures RAII
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &VCO);
    glDeleteBuffers(1, &IBO);
}

void Mesh::Draw() const
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::Initialize(const std::vector<Vertex> &_vertices, const std::vector<unsigned int> &_indices)
{
    if (VAO != 0)
    {
        // TODO: Add throw or println
        return;
    }
    // Generate Buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VCO);
    glGenBuffers(1, &VUO);
    glGenBuffers(1, &IBO);
    // Setup Values
    vertices = _vertices;
    indices = _indices;

    // Extract vert position and colour data into arrays
    std::vector<glm::vec3> vertexPositions;
    std::vector<glm::vec4> vertexColours;
    std::vector<glm::vec2> vertexUV;
    for (const auto &vertex : vertices)
    {
        vertexPositions.push_back(vertex.position);
        vertexColours.push_back(vertex.color);
        vertexUV.push_back(vertex.uv);
    }

    // Setup and Assign VAO

    glBindVertexArray(VAO);

    // Setup VBO

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexPositions.size() * sizeof(glm::vec3), vertexPositions.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);
    glEnableVertexAttribArray(0);

    // Setup VBO for Colour Data

    glBindBuffer(GL_ARRAY_BUFFER, VCO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * vertexColours.size(), vertexColours.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void *)0);
    glEnableVertexAttribArray(1);

    // Setup VBO for UV Data
    glBindBuffer(GL_ARRAY_BUFFER, VUO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * vertexUV.size(), vertexUV.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *)0);
    glEnableVertexAttribArray(2);

    // Setup Element Index Buffer

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
    glBindVertexArray(0);
}

