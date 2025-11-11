#include <PRISM/Renderer/Mesh.h>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
Mesh::Mesh(const std::vector<Vertex> &_vertices, const std::vector<unsigned int> &_indices)
{
    Initialize(_vertices, _indices);
}

Mesh::~Mesh()
{
    // Emsures RAII
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
}

void Mesh::Draw() const
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::CalculateNormals()
{
    // Loop through each triangle and calculate normals via cross product
    for (int i = 0; i < indices.size(); i += 3)
    {
        // Loop over in 3s for each face then we use that face to calculate the normals for each one
        // V1 - V0 Cross V2 - V0
        glm::vec3 normal = glm::cross(
            vertices[indices[i + 1]].position - vertices[indices[i]].position,
            vertices[indices[i + 2]].position - vertices[indices[i]].position);
        for(int j = i; j < i + 3; j++)
        {
            vertices[indices[j]].normal += normal;
        }
    }
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
    glGenBuffers(1, &IBO);
    // Setup Values
    vertices = _vertices;
    indices = _indices;

    // Setup and Assign VAO

    glBindVertexArray(VAO);

    // Setup VBO

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // Setup Element Index Buffer

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    // New Interleaved Data

    GLsizei stride = sizeof(Vertex);

    // Position
    // OFFSETOF Macro is very handy use more often
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // Colour
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(Vertex, colour));
    glEnableVertexAttribArray(1);

    // Setup VBO for UV Data

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(Vertex, uv));
    glEnableVertexAttribArray(2);

    // Setup VBO for Normal Data

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(Vertex, normal));

    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}
