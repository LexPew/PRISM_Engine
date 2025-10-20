#include <PRISM/Utils/PMath.h>
#include <cmath>


float PMath::RandomRange(float min, float max)
{
    //TODO: Read up on how this actually works thank you chatgpt for this
    float t = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // [0, 1)
    return min + t * (max - min);  // Scale to [min, max)
}

float PMath::Clamp(float value, float min, float max)
{
    return std::min((std::max(value,min)), max);

}
