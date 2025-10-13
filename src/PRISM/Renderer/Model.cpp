#include <PRISM/Renderer/Model.h>
#include <glad/glad.h>


Model::Model(const glm::vec3 &_position, const std::vector<Vertex> &_vertices, const std::vector<unsigned int> &_indices)
{
    // Generate Buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VCO);
    glGenBuffers(1, &IBO);
    // Setup Values
    position = _position;
    vertices = _vertices;
    indices = _indices;

    // Extract vert position and colour data into arrays
    std::vector<glm::vec3> vertexPositions;
    std::vector<glm::vec4> vertexColours;

    for (const auto &vertex : vertices)
    {
        vertexPositions.push_back(vertex.position);
        vertexColours.push_back(vertex.color);
    }

    // Setup and Assign VAO

    glBindVertexArray(VAO);

    // Setup VBO

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), vertexPositions.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);
    glEnableVertexAttribArray(0);

    // Setup VBO for Colour Data


    glBindBuffer(GL_ARRAY_BUFFER, VCO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * vertices.size(), vertexColours.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void *)0);
    glEnableVertexAttribArray(1);

    // Setup Element Index Buffer

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
    glBindVertexArray(0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Model::~Model()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &VCO);
    glDeleteBuffers(1, &IBO);
}
void Model::Draw() const
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}