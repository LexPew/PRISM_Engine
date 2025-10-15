#include <PRISM/Utils/PMath.h>


float PMath::RandomRange(float min, float max)
{
    //Rand() % num = 0 to (num - 1)
    int range = static_cast<int>(max - min + 1.0f);
    return static_cast<float>(rand() % range) + min;
}