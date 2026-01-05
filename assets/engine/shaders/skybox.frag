#version 330 core
out vec4 FragColor;
in vec3 tex_Coords;

uniform samplerCube skybox;
void main()
{
    FragColor = texture(skybox,tex_Coords);
}