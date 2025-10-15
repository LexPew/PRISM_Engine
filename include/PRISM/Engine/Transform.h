#include <glm/glm.hpp>

struct Transform
{
    glm::vec3 position{0, 0, 0};
    glm::vec3 rotation{0, 0, 0};
    glm::vec3 scale{1, 1, 1};

    glm::vec3 forward() const
    {
        glm::vec3 forward(0,0,0);
        float pitch = glm::radians(rotation.x);
        float yaw = glm::radians(rotation.y);

        forward.x = cos(pitch) * sin(yaw);
        forward.y = sin(pitch);
        forward.z = -cos(pitch) * cos(yaw);

        return forward;
    }

    glm::vec3 right() const
    {
        return glm::cross(forward(), {0,1,0}); // This will return the cross of forward and up aka right
    }

    glm::vec3 up() const
    {
        return glm::cross(right(), forward());
    }
};