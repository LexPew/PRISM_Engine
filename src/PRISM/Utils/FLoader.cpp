#include <PRISM/Utils/FLoader.h>

#include <fstream>
#include <sstream>
#include <fmt/core.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyObjLoader/tiny_obj_loader.h>

#include <vector>
#include <PRISM/Utils/PMath.h>

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
Mesh FLoader::LoadObject(const std::string &path)
{
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
        return Mesh(); // return empty mesh if loading fails
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
                attrib.vertices[index.vertex_index * 3 + 2]
            };

            //TODO: Update
            glm::vec4 vertexColour = glm::vec4(PMath::RandomRange(0.0f, 1.0f), PMath::RandomRange(0.0f, 1.0f), PMath::RandomRange(0.0f, 1.0f), 1.0f);

            Vertex vert(position, vertexColour);
            vertices.push_back(vert);
            indices.push_back(static_cast<unsigned int>(j));
        }
    }

    return Mesh(vertices, indices);
}
