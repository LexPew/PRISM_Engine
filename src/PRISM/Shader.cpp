#include <PRISM/Shader.h>

#include <glad/glad.h>
#include <fmt/core.h>



Shader::~Shader()
{
    glDeleteProgram(programId);
    programId = 0;
}

bool Shader::Initialize()
{
    // TODO: Update the messy if statement usage and actually return something if
    // we fail to compile parts

    //C Str Conversion
    const char* vSource = vertexSource.c_str();
    const char* fSource = fragmentSource.c_str();


    // Create the vertex and fragment shaders and check if the compiled
    unsigned int vertexShader, fragmentShader;
    int success;
    char infoLog[512];
    
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1,  &vSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        fmt::println("Shader Error: {}", infoLog);
        glDeleteShader(vertexShader);
        return false;
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        fmt::println("Shader Error: {}", infoLog);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;
    }

    programId = glCreateProgram();
    glAttachShader(programId, vertexShader);
    glAttachShader(programId, fragmentShader);
    glLinkProgram(programId);

    // Check shader compiled
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success)
    {

        glGetProgramInfoLog(programId, 512, NULL, infoLog);
        fmt::println("Shader Error: {}", infoLog);
        glDeleteProgram(programId);
        programId = 0;
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

void Shader::Enable()
{
    glUseProgram(programId);
}
