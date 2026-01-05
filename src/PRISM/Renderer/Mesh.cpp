#include <PRISM/Renderer/Mesh.h>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
Mesh::Mesh(const std::vector<Vertex> &_vertices, const std::vector<unsigned int> &_indices)
{
    Initialize(_vertices, _indices);
}

Mesh::~Mesh()
{
    // Ensures RAII
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
    // Reset all normals
    for (auto &v : vertices)
    {
        v.normal = {0, 0, 0};
    }
    // Calculate normal based on faced

    // i + 2 ensures we dont go out of bounds
    for (size_t i = 0; i + 2 < indices.size(); i += 3)
    {
        unsigned int v0 = indices[i];
        unsigned int v1 = indices[i + 1];
        unsigned int v2 = indices[i + 2];

        glm::vec3 edge1 = vertices[v0].position - vertices[v1].position;
        glm::vec3 edge2 = vertices[v2].position - vertices[v1].position;
        glm::vec3 normal = glm::cross(edge1, edge2);
        normal = glm::normalize(normal);

        vertices[v0].normal = normal;
        vertices[v1].normal = normal;
        vertices[v2].normal = normal;
    }
    // Need to re-upload normal data to GPU
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Update only normal data
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        glBufferSubData(GL_ARRAY_BUFFER, i * sizeof(Vertex) + offsetof(Vertex, normal), sizeof(glm::vec3), glm::value_ptr(vertices[i].normal));
    
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
        // Using offsetof macro to specify the offset of the position attribute in Vertex
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
