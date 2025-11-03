#version 330 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec4 inColour;
layout (location = 2) in vec2 inUV;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 vertexColour;
out vec2 uv;
void main()
{
    //PVM
    gl_Position = projection * view * model * vec4(inPos,1.0);
    vertexColour = inColour;
    uv = inUV;

}