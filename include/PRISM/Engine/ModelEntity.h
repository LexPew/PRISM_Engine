#pragma once
#include <PRISM/Engine/Entity.h>
#include <PRISM/Renderer/Mesh.h>
#include <PRISM/Renderer/Texture.h>

#include <memory>

// TODO: Update comments
class ModelEntity : public Entity
{
private:
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Texture> texture = Texture::CreateDefault();

public:
    ModelEntity() {};

    const std::shared_ptr<Mesh> &GetMesh() const { return mesh; }

    void SetMesh(const std::shared_ptr<Mesh> &newMesh)
    {
        mesh = newMesh;
    };

    void SetTexture(const std::shared_ptr<Texture> &newTexture)
    {
        if (newTexture)
        {
            texture = newTexture;
        }
    }

    void Draw() override;
};