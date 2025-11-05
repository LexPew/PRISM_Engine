#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>
class Vertex
{
public:
    glm::vec3 position{0,0,0};
    glm::vec4 colour{0,0,0,0};
    glm::vec2 uv{0,0};
    glm::vec3 normal{0,0,0};

    Vertex(const glm::vec3& p_position, const glm::vec4& p_color, const glm::vec2& p_uv, const glm::vec3 p_normal)
    : position(p_position), colour(p_color), uv(p_uv), normal(p_normal){};
};