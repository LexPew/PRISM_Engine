#pragma once
#include <PRISM/Engine/CameraEntity.h>
#include <glm/vec2.hpp>

// TODO: Add a way to exit from captured mouse pos on escp and reenter when clicking
class OrbitalCameraEntity : public CameraEntity
{
private:
    glm::vec2 lastMousePos{0, 0};
    float moveSpeed{10.0f};
    float sprintMultiplier{5.0f};
    float turnSpeed{10.0f};

public:
    void Start();
    void Update(float deltaTime) override;

private:
    void ScrollSpeed();
};