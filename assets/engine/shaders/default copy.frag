#version 330 core

// Struct to define a basic light
struct Light
{
    bool light_active;
    vec3 light_position;    // Position of the light in world space
    float light_intensity;  // Intensity / strength of the light
    float light_attenuation; //How far the light travels
};

// Output of the fragment shader
out vec4 FragColor;

// Uniforms
uniform Light lights[10];        // Array of lights (max 10)
uniform sampler2D input_Texture; // Texture applied to the object
uniform vec3 directional_Light;  // Directional light vector
uniform bool debug_Vertex = false;       // Debug flag to show vertex colors
uniform bool debug_Normal = false;     // Debug flag to show normal colors
uniform vec3 ambient_Light;
// Inputs from the vertex shader
in vec4 frag_Vertex_Colour;   // Interpolated vertex color
in vec2 frag_Vertex_UV;       // Interpolated UV coordinates
in vec3 frag_Vertex_Normal;   // Interpolated normal in world space
in vec3 frag_Position;        // Fragment position in world space
uniform vec3 view_Position;        // Camera position in world space


float specularStrength = .5;
vec3 specularColour = vec3(1.0);

vec4 CalculateLighting()
{
        //Specular defaults to white light
        vec3 specular = vec3(0.0);
        vec3 viewDir = normalize(view_Position - frag_Position);

        // Normalize the interpolated normal for lighting calculations
        vec3 normal = normalize(frag_Vertex_Normal);


        //Directional Light
        vec3 l_directional = normalize(-directional_Light);
        float i_directional = max(0, dot(l_directional, normal));
        float diffuseIntensity = i_directional;

        //Specular Directional
        vec3 halfWayDir = normalize(l_directional+ viewDir);
        float spec = pow(max(dot(normal, halfWayDir), 0), 32);
        specular += vec3(spec * specularStrength) * specularColour;
        for(int i = 0; i < 10; i++)
        {
            if(lights[i].light_active)
            {
                vec3 l_spot = normalize(lights[i].light_position - frag_Position);
                float i_spot = max(0,dot(l_spot, normal));
                float distance = length(lights[i].light_position - frag_Position);
                float attenuation_spot = 1.0 - smoothstep(0, lights[i].light_attenuation, distance);

                i_spot *= attenuation_spot;
                diffuseIntensity += i_spot;

                //Specular for spot light
                vec3 halfWayDir_spot = normalize(l_spot + viewDir);
                float spec_spot = pow(max(dot(normal, halfWayDir_spot), 0), 32);
                specular += vec3(spec_spot * specularStrength * attenuation_spot) * specularColour;
            }
            
        }
      
        // Ambient contribution, tinted by tex colour (from uniform)
        vec3 texColour = vec3(texture(input_Texture,frag_Vertex_UV));
        vec3 ambient = ambient_Light * texColour;

        // Diffuse contribution using the texture color and diffuse intensity
        vec3 diffuse = diffuseIntensity * texColour;

        // Combine ambient and diffuse for final color
        vec4 finalColor = vec4(ambient + diffuse + specular, 1.0);
        return finalColor;
}
void main()
{
    if(debug_Vertex){
        FragColor = frag_Vertex_Colour;
    }
    else if(debug_Normal){
        FragColor = vec4(frag_Vertex_Normal,1);
    }
    else{
        FragColor = CalculateLighting();
    }
    
}
