#pragma once

#include <PRISM/Engine/Entity.h>

class CameraEntity: public Entity
{
public:
    float fov{70.0f};
    float near{0.01f};
    float far{100.0f};

    void Update(float deltaTime) override;
};