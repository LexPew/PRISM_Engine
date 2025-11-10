#pragma once

#include <PRISM/Engine/Scene.h>

class TerrainScene : public Scene
{
private:
public:
    TerrainScene(){};
    void Start() override;
    void Panel() override;
};