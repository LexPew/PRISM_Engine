#include <PRISM/Engine/ModelEntity.h>
#include <PRISM/Renderer/Renderer.h>
#include <fmt/core.h>
void ModelEntity::Draw()
{
    Renderer::Get()->Draw(mesh, transform.position, transform.rotation, transform.scale);

}