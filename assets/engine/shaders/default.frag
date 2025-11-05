#version 330 core

// Struct to define a basic light
struct Light
{
    vec3 light_position;    // Position of the light in world space
    float light_intensity;  // Intensity / strength of the light
    float light_attentuaion; //How far the light travels
};

// Output of the fragment shader
out vec4 FragColor;

// Uniforms
uniform Light lights[1];        // Array of lights (max 10)
uniform sampler2D input_Texture; // Texture applied to the object
uniform vec3 directional_Light;  // Directional light vector
uniform bool debug_Vertex;       // Debug flag to show vertex colors

// Inputs from the vertex shader
in vec4 frag_Vertex_Colour;   // Interpolated vertex color
in vec2 frag_Vertex_UV;       // Interpolated UV coordinates
in vec3 frag_Vertex_Normal;   // Interpolated normal in world space
in vec3 frag_Ambient_Light;   // Ambient light contribution
in vec3 frag_Position;        // Fragment position in world space

void main()
{
    // If not in debug mode, calculate lighting
    if(debug_Vertex == false)
    {
        // Normalize the interpolated normal for lighting calculations
        vec3 normalizedNormal = normalize(frag_Vertex_Normal);

        // Direction of the directional light (negative because light points toward the surface)
        vec3 lightDirection = normalize(-directional_Light);

        // Compute diffuse intensity using Lambert's cosine law
        float diffuseIntensity = max(0, dot(lightDirection, normalizedNormal));

        // Ambient contribution (from uniform)
        vec3 ambient = frag_Ambient_Light;

        // Diffuse contribution using the texture color and diffuse intensity
        vec3 diffuse = diffuseIntensity * vec3(texture(input_Texture, frag_Vertex_UV));

        // Combine ambient and diffuse for final color
        FragColor = vec4(ambient + diffuse, 1.0);
    }
    else
    {
        // Debug mode: output the vertex color directly
        FragColor = frag_Vertex_Colour;
    }
}
