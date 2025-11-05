#include <PRISM/Utils/PMath.h>
#include <cmath>

float PMath::RandomRange(float min, float max)
{
    float t = (float)rand() / (float)RAND_MAX; // This gives a value between 0-1

    // We start with our minimum number then add the multiplied value which will never go above max as its max - min
    float randomNumber = min + t * (max - min);

    return randomNumber;

    // EXAMPLE
    // Min = 10, Max = 30, we need a number between 10-30 inclusive
    // SO 10 + 0.5 * (30 - 10);
    //  10 + 10 = 20
}

float PMath::Clamp(float value, float min, float max)
{
    return std::min((std::max(value, min)), max);
}
