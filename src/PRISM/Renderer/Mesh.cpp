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
    glGenBuffers(1, &IBO);
    // Setup Values
    vertices = _vertices;
    indices = _indices;

    // Setup and Assign VAO

    glBindVertexArray(VAO);

    // Setup VBO

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,  vertices.size() *sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);


     // Setup Element Index Buffer

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    //New Interleaved Data

    GLsizei stride = sizeof(Vertex);

    //Position
    //OFFSETOF Macro is very handy use more often
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex,position));
    glEnableVertexAttribArray(0);

    //Colour
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex,colour));
    glEnableVertexAttribArray(1);

    // Setup VBO for UV Data

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(Vertex,uv));
    glEnableVertexAttribArray(2);

    // Setup VBO for Normal Data

    glVertexAttribPointer(3,3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex,normal));
    glEnableVertexAttribArray(3);

   
    glBindVertexArray(0);
}

