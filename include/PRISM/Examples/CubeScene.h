#pragma once
#include <PRISM/Engine/Scene.h>
class CubeScene : public Scene
{
    public:
    CubeScene(){};

    void Start() override;
    void Update(float deltaTime) override;

};