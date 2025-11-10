#pragma once
#include <PRISM/Engine/Entity.h>
//TODO: Add colour, attentuaion, etc
class Light : public Entity
{
private:
    unsigned int lightId;
    float intensity{1.0f};
    float attenuation{50.0f};
    bool update{false};
public:
    Light(float p_intensity): intensity(p_intensity){};
    ~Light();
    void Start() override;
    void Update(float deltaTime) override;

    void SetAttenuation(const float newAttenuation){attenuation = newAttenuation; update = true;}
};