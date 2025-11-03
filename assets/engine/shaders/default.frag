#version 330 core
out vec4 FragColor;

in vec4 vertexColour;

uniform sampler2D inTexture;

in vec2 uv;

void main()
{
    //FragColor = vec4(ourCol.x, ourCol.y, ourCol.z, 1.0); 
    FragColor = texture(inTexture, uv) * (vertexColour);
}
