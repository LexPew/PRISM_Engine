#pragma once

#include <string>
#include <glm/mat4x4.hpp>
// Enum for sending matrices MVP
enum MatrixType
{
    MatrixModel,
    MatrixView,
    MatrixProjection
};

class Shader
{
private:
    // Program ID
    unsigned int programId{0}; // 0 No shader set

    std::string vertexSource;
    std::string fragmentSource;

    unsigned int modelLocation{0};
    unsigned int viewLocation{0};
    unsigned int projectionLocation{0};

public:
    // Creates a new shader with the given vertex and fragments shader
    Shader(const std::string &vertexSource, const std::string &fragmentSource) : vertexSource(vertexSource), fragmentSource(fragmentSource) {};

    ~Shader();

    // Links and compiles shader
    bool Initialize();
    // Finds uniform locations
    void FindUniforms();
    // Enables the shader
    void Enable();

    // Send Matrices
    void UpdateMatrix(const MatrixType type, const glm::mat4 &matrix);

    const unsigned int GetProgramId() const { return programId; };
};