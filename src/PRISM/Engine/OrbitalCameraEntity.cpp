#include <PRISM/Engine/OrbitalCameraEntity.h>
#include <PRISM/Renderer/Renderer.h>
#include <fmt/core.h>
#include <GLFW/glfw3.h>

void OribitalCameraEntity::Start()
{
    glfwSetInputMode(Renderer::Instance->GetWindow()->GetGlfwWindow(),
                     GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void OribitalCameraEntity::Update(float deltaTime)
{

    double currentX, currentY;
    glfwGetCursorPos(Renderer::Instance->GetWindow()->GetGlfwWindow(), &currentX, &currentY);
    glm::vec2 currentMousePos{currentX, currentY};
    glm::vec2 delta = lastMousePos - currentMousePos;

    lastMousePos = currentMousePos;

    transform.rotation.y -= delta.x * turnSpeed * deltaTime;
    transform.rotation.x += delta.y * turnSpeed * deltaTime;



    glm::vec3 move(0,0,0);
    if (glfwGetKey(Renderer::Instance->GetWindow()->GetGlfwWindow(), GLFW_KEY_W))
    {
        move.z += 1;
    }
    else if (glfwGetKey(Renderer::Instance->GetWindow()->GetGlfwWindow(), GLFW_KEY_S))
    {
        move.z -= 1;
    }

        if (glfwGetKey(Renderer::Instance->GetWindow()->GetGlfwWindow(), GLFW_KEY_A))
    {
        move.x -= 1;
    }
    else if (glfwGetKey(Renderer::Instance->GetWindow()->GetGlfwWindow(), GLFW_KEY_D))
    {
        move.x += 1;
    }
    move = glm::normalize(move);
    move = move * moveSpeed * deltaTime;
if (glm::length(move) > 0.0f)
{
    move = glm::normalize(move);

    glm::vec3 forward = transform.forward();
    glm::vec3 right   = transform.right();

    transform.position += (forward * move.z + right * move.x) * moveSpeed * deltaTime;
}
    CameraEntity::Update(deltaTime);
}
