#include <PRISM/Engine/CameraEntity.h>
#include <PRISM/Renderer/Renderer.h>
#include <fmt/core.h>
void CameraEntity::Update(float deltaTime)
{
    // Send camera matrices to the renderer

    Renderer::Get()->SendCameraMatrices(this);

}