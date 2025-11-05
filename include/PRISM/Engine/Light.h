#pragma once
#include <PRISM/Engine/Entity.h>
//TODO: Add colour, attentuaion, etc
class Light : public Entity
{
private:
    unsigned int lightId;
    float intensity{0.5f};

public:
    Light(float p_intensity): intensity(p_intensity){};
    void Start() override;
    void Update(float deltaTime) override;
};