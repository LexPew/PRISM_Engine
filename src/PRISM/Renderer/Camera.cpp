#include <PRISM/Renderer/Camera.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <fmt/core.h>
Camera::Camera(int screenWidth, int screenHeight, float _fov, float _near, float _far)
{
    fov = _fov;
    near = _near;
    far = _far;
    // Intialize matrices
    projectionMatrix = glm::perspective(fov, ((float)screenWidth / (float)screenHeight), near, far);
    SetPosition(position);
}
void Camera::SetPosition(const glm::vec3 &newPosition)
{
    position = newPosition;
    viewMatrix = glm::lookAt(position, target, up);
}