#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
struct Transform
{
    glm::vec3 position{0, 0, 0};
    glm::vec3 rotation{0, 0, 0};
    glm::vec3 scale{1, 1, 1};


    glm::mat4 GetMatrix()
    {
        // Recalculate matrix
        glm::mat4 matrix{1.0f};
        matrix = glm::translate(matrix, position);
        matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
        matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
        matrix = glm::scale(matrix, scale);
        return matrix;
    }
    
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

    //Calculate rotation to look at a target point
    void LookAt(const glm::vec3& target){
        glm::vec3 direction = glm::normalize(target - position);
        float pitch = glm::degrees(asin(direction.y));
        float yaw = glm::degrees(atan2(direction.x, -direction.z));

        rotation.x = pitch;
        rotation.y = yaw;
    };
};