#pragma once
#include <string>

class Shader
{
public:
    // Program ID
    unsigned int programId{0}; //0 No shader set

    std::string vertexSource;
    std::string fragmentSource;


    // Creates a new shader with the given vertex and fragments shader
    Shader(const std::string& vertexSource, const std::string& fragmentSource) : vertexSource(vertexSource), fragmentSource(fragmentSource){};

    ~Shader();

    //Links and compiles shader
    bool Initialize();
    // Enables the shader
    void Enable();
};