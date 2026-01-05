#version 330 core

//Vertex Inputs
layout (location = 0) in vec3 vertex_Position;

//Matrices

uniform mat4 view;
uniform mat4 projection;

//Outputs
out vec3 tex_Coords;

void main()
{
    tex_Coords = vertex_Position;
    //We remove the model matrix since we want the skybox to always be centered on the camera
    gl_Position = projection * view * vec4(vertex_Position, 1.0);
}