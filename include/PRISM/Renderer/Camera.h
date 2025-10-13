#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera
{
private:
    glm::vec3 position{0, 0, 15.0f};
    glm::vec3 target{0, 0, 0}; //Default to looking forward by one unit
    glm::vec3 up{0, 1, 0};

    float near{0.1f};
    float far{100.0f};
    float fov{70.0f};

    // Matrices
    glm::mat4x4 viewMatrix;
    glm::mat4x4 projectionMatrix;

public:
    Camera(int screenWidth, int screenHeight, float _fov, float _near, float _far);

    const glm::mat4x4 &GetViewMatrix() { return viewMatrix; };
    const glm::mat4x4 &GetProjectionMatrix() { return projectionMatrix; };

    const glm::vec3& GetPosition(){return position;};
    void SetPosition(const glm::vec3& newPosition);
};