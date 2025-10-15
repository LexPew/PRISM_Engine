#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
class PMath
{
public:
    static void InitializeRandom(float random) { srand(random); };
    static float RandomRange(float min, float max);

};