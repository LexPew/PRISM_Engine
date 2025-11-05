#include <PRISM/Utils/FLoader.h>

#include <fstream>
#include <sstream>
#include <fmt/core.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyObjLoader/tiny_obj_loader.h>

#include <vector>
#include <PRISM/Utils/PMath.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
std::string FLoader::LoadFile(const std::string &path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        fmt::println("FLoader Error: Failed to open file {}", path);
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
std::shared_ptr<Mesh> FLoader::LoadObject(const std::string &path)
{
    //TODO: Implement Materials And Heirarchy
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    bool success = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str());
    if (!warn.empty())
        fmt::println("TinyObj warning: {}", warn);
    if (!success)
    {
        fmt::println("TinyObj error: {}", err);
        return nullptr;
    }

    // Loop over all shapes
    for (size_t i = 0; i < shapes.size(); ++i)
    {
        const tinyobj::mesh_t &mesh = shapes[i].mesh;

        // Loop over all indices
        for (size_t j = 0; j < mesh.indices.size(); ++j)
        {
            const tinyobj::index_t &index = mesh.indices[j];

            glm::vec3 position = {
                attrib.vertices[index.vertex_index * 3 + 0],
                attrib.vertices[index.vertex_index * 3 + 1],
                attrib.vertices[index.vertex_index * 3 + 2]};

            glm::vec2 uv = {
                attrib.texcoords[index.texcoord_index * 2 + 0],
                attrib.texcoords[index.texcoord_index * 2 + 1],

            };

            glm::vec3 normal = {
                attrib.normals[index.normal_index * 3 + 0],
                attrib.normals[index.normal_index * 3 + 1],
                attrib.normals[index.normal_index * 3 + 2]};

            //HACK: There is no vertex colours with objs so we just use the normals
            glm::vec4 vertexColour = glm::vec4(
                PMath::Clamp((normal.x + 1.0f) * 0.5f, 0.0f, 1.0f),
                PMath::Clamp((normal.y + 1.0f) * 0.5f, 0.0f, 1.0f),
                PMath::Clamp((normal.z + 1.0f) * 0.5f, 0.0f, 1.0f),
                1.0f);

            Vertex vert(position, vertexColour, uv, normal);
            vertices.push_back(vert);
            indices.push_back(static_cast<unsigned int>(j));
        }
    }
    

    fmt::println("Loaded object with {} vertices and {} indices", vertices.size(), indices.size());

    auto mesh = std::make_shared<Mesh>(vertices, indices);
    return mesh;
}

ImageData FLoader::LoadImage(const std::string &path)
{
    ImageData image;
    
    image.data = stbi_load(path.c_str(), &image.width, &image.height, &image.channels, image.channels); 

    if(!image.data){
        fmt::println("Error: Failed to load image");
        return image;
    }else{
        fmt::println("Loaded image with size: {}x{} and channels: {}", image.width, image.height, image.channels);
    }



    return image;
}
