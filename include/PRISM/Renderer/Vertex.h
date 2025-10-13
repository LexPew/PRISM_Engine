#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
class Vertex
{
public:
    glm::vec3 position{0,0,0};
    glm::vec4 color{0,0,0,0};

    Vertex(const glm::vec3& _position, const glm::vec4& _color): position(_position), color(_color){};
};