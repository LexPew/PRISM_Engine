#pragma once
#include <PRISM/Engine/Entity.h>
#include <PRISM/Renderer/Mesh.h>

class ModelEntity : public Entity
{
private:
    Mesh mesh;
public:

    ModelEntity(){};

    const Mesh& GetMesh() const {return mesh;};

    void SetMesh(const Mesh& newMesh){mesh = newMesh;};

    void Draw() override;
};