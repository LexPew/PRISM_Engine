#include <PRISM/Engine/OrbitalCameraEntity.h>
#include <PRISM/Renderer/Renderer.h>
#include <PRISM/Core/Input/Input.h>
#include <PRISM/Core/Window.h>
#include <PRISM/Utils/PMath.h>
#include <GLFW/glfw3.h>
#include <fmt/core.h>

void OrbitalCameraEntity::Start()
{
    Input::Get().SetCursorLockState(true);
}

void OrbitalCameraEntity::Update(float deltaTime)
{
    ScrollSpeed();


    // Lock cursor on left click && we are not clicking on ImGui windows
    if (Input::Get().GetMouse().GetMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT) && !Input::Get().GetMouse().ImGuiCursorCheck())
    {
       Input::Get().SetCursorLockState(true);
    }

    //Dont update camera movement or rotation if cursor is unlocked
    if(!Input::Get().IsCursorLocked())
    {
        CameraEntity::Update(deltaTime);
        return;
    }
    const glm::vec2& delta = Input::Get().GetMouse().GetMouseDelta();

    // Update camera rotation
    GetLocalTransform().rotation.y += delta.x * turnSpeed * deltaTime;
    GetLocalTransform().rotation.x -= delta.y * turnSpeed * deltaTime;

  
    GetLocalTransform().rotation.x = PMath::Clamp(GetLocalTransform().rotation.x, -89.9f, 89.9f);

    // Movement speed (handle sprint)
    float currentMoveSpeed = moveSpeed;
    if (Input::Get().IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
        currentMoveSpeed *= sprintMultiplier;

    // Build movement direction
    glm::vec3 move(0.0f);
    if (Input::Get().IsKeyPressed(GLFW_KEY_W)) move.z += 1.0f;
    if (Input::Get().IsKeyPressed(GLFW_KEY_S)) move.z -= 1.0f;
    if (Input::Get().IsKeyPressed(GLFW_KEY_A)) move.x -= 1.0f;
    if (Input::Get().IsKeyPressed(GLFW_KEY_D)) move.x += 1.0f;

    if (glm::length(move) > 0.0f)
    {
        move = glm::normalize(move);

        const glm::vec3 forward = GetLocalTransform().forward();
        const glm::vec3 right   = glm::normalize(GetLocalTransform().right()); //Fixes completey vertical bug

        GetLocalTransform().position += (forward * move.z + right * move.x) * currentMoveSpeed * deltaTime;
 
    }

    CameraEntity::Update(deltaTime);
}

void OrbitalCameraEntity::ScrollSpeed()
{
    moveSpeed += Input::Get().GetMouse().GetScrollDelta();
    moveSpeed = std::max(1.0f, moveSpeed);
}
