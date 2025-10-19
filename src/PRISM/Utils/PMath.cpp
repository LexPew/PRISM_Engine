#include <PRISM/Utils/PMath.h>


float PMath::RandomRange(float min, float max)
{
    //TODO: Read up on how this actually works thank you chatgpt for this
    float t = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // [0, 1)
    return min + t * (max - min);  // Scale to [min, max)
}
