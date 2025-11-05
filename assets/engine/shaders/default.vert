#version 330 core







//Vertex Inputs
layout (location = 0) in vec3 vertex_Position;
layout (location = 1) in vec4 vertex_Colour;
layout (location = 2) in vec2 vertex_UV;
layout (location = 3) in vec3 vertex_Normal;

//Matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//Lighting
uniform vec3 ambient_Light;



//Outputs
out vec4 frag_Vertex_Colour;
out vec2 frag_Vertex_UV;
out vec3 frag_Ambient_Light;
out vec3 frag_Vertex_Normal;
out vec3 frag_Position;

void main()
{
    //PVM
    gl_Position = projection * view * model * vec4(vertex_Position,1.0);

    //Outputs

    frag_Vertex_Colour = vertex_Colour;
    frag_Vertex_UV = vertex_UV;
    frag_Ambient_Light = ambient_Light;


    //Extract the upper left bit of the model matrix, so we only get rotation and scaling. Since we apply normal in object space
    //Inverse corrects scaling which would affect normals
    //Trnaspose keeps normals perpedicular 
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    frag_Vertex_Normal = normalize(normalMatrix * vertex_Normal);


    frag_Position = vec3(model * vec4(vertex_Position, 1.0));

}