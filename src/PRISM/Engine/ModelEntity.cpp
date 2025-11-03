#include <PRISM/Engine/ModelEntity.h>
#include <PRISM/Renderer/Renderer.h>
#include <fmt/core.h>


void ModelEntity::Draw()
{

    if (texture == nullptr)
    {
        fmt::println("texture is null");

    }
    else
    {
        texture->Bind();
    }

    if (!mesh)
    {
        fmt::println("mesh is null");
        return;
    }
    else
    {
        Renderer::Get().Draw(mesh, transform.position, transform.rotation, transform.scale);
    }
}
