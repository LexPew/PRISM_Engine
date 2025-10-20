#include <PRISM/Engine/OrbitalCameraEntity.h>
#include <PRISM/Renderer/Renderer.h>
#include <PRISM/Core/Input/Input.h>
#include <PRISM/Core/Window.h>
#include <PRISM/Utils/PMath.h>
#include <GLFW/glfw3.h>
#include <fmt/core.h>

void OrbitalCameraEntity::Start()
{
    Input::Instance->SetCursorLockState(true);
}

void OrbitalCameraEntity::Update(float deltaTime)
{
    ScrollSpeed();

    const glm::vec2& delta = Input::Instance->GetMouse().GetMouseDelta();

    // Update camera rotation
    transform.rotation.y += delta.x * turnSpeed * deltaTime;
    transform.rotation.x -= delta.y * turnSpeed * deltaTime;
    transform.rotation.x = PMath::Clamp(transform.rotation.x, -89.9f, 89.9f);

    // Lock cursor on left click
    if (Input::Instance->GetMouse().GetMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
        Input::Instance->SetCursorLockState(true);

    // Movement speed (handle sprint)
    float currentMoveSpeed = moveSpeed;
    if (Input::Instance->IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
        currentMoveSpeed *= sprintMultiplier;

    // Build movement direction
    glm::vec3 move(0.0f);
    if (Input::Instance->IsKeyPressed(GLFW_KEY_W)) move.z += 1.0f;
    if (Input::Instance->IsKeyPressed(GLFW_KEY_S)) move.z -= 1.0f;
    if (Input::Instance->IsKeyPressed(GLFW_KEY_A)) move.x -= 1.0f;
    if (Input::Instance->IsKeyPressed(GLFW_KEY_D)) move.x += 1.0f;

    if (glm::length(move) > 0.0f)
    {
        move = glm::normalize(move);

        const glm::vec3 forward = transform.forward();
        const glm::vec3 right   = glm::normalize(transform.right()); //Fixes completey vertical bug

        transform.position += (forward * move.z + right * move.x) * currentMoveSpeed * deltaTime;
    }

    CameraEntity::Update(deltaTime);
}

void OrbitalCameraEntity::ScrollSpeed()
{
    moveSpeed += Input::Instance->GetMouse().GetScrollDelta();
    moveSpeed = std::max(1.0f, moveSpeed);
}
