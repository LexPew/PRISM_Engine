#pragma once
#include <PRISM/Engine/Scene.h>
#include <PRISM/Engine/ModelEntity.h>
#include <PRISM/Engine/OrbitalCameraEntity.h>
class CubeScene : public Scene
{
private:
public:
    CubeScene() {};

    void Start() override;
    void Update(float deltaTime) override;
};