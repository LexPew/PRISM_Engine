#include <PRISM/Engine/OrbitalCameraEntity.h>
#include <PRISM/Renderer/Renderer.h>

#include <GLFW/glfw3.h>
#include <PRISM/Core/Input/Input.h>
#include <PRISM/Core/Window.h>
#include <fmt/core.h>
void OribitalCameraEntity::Start()
{
    Input::Instance->SetCursorLockState(true);
}
void OribitalCameraEntity::Update(float deltaTime)
{
    ScrollSpeed();
    const glm::vec2 &delta = Input::Instance->GetMouse().GetMouseDelta();

    transform.rotation.y += delta.x * turnSpeed * deltaTime;
    transform.rotation.x -= delta.y * turnSpeed * deltaTime;

    if (Input::Instance->GetMouse().GetMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
    {

        Input::Instance->SetCursorLockState(true);
    }

    float currentMoveSpeed = moveSpeed;
    if (Input::Instance->IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
    {
        currentMoveSpeed = currentMoveSpeed * sprintMultiplier;
    }
    glm::vec3 move(0, 0, 0);
    if (Input::Instance->IsKeyPressed(GLFW_KEY_W))
    {
        move.z += 1;
    }
    else if (Input::Instance->IsKeyPressed(GLFW_KEY_S))
    {
        move.z -= 1;
    }

    if (Input::Instance->IsKeyPressed(GLFW_KEY_A))
    {
        move.x -= 1;
    }
    else if (Input::Instance->IsKeyPressed(GLFW_KEY_D))
    {
        move.x += 1;
    }
    move = glm::normalize(move);
    move = move * currentMoveSpeed * deltaTime;
    if (glm::length(move) > 0.0f)
    {
        move = glm::normalize(move);

        glm::vec3 forward = transform.forward();
        glm::vec3 right = transform.right();

        transform.position += (forward * move.z + right * move.x) * currentMoveSpeed * deltaTime;
    }
    CameraEntity::Update(deltaTime);
}

void OribitalCameraEntity::ScrollSpeed()
{

    moveSpeed += Input::Instance->GetMouse().GetScrollDelta();
    moveSpeed = std::max(1.0f, moveSpeed);
}
