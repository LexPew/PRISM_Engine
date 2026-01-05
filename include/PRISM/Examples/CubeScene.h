#pragma once
#include <PRISM/Engine/Scene.h>
#include <PRISM/Engine/ModelEntity.h>
#include <PRISM/Engine/OrbitalCameraEntity.h>
class CubeScene : public Scene
{
private:
//Non rotating camera and floor
    std::shared_ptr<OrbitalCameraEntity> camera{nullptr};

public:
    CubeScene() {};

    void Start() override;
    void Update(float deltaTime) override;
};