#pragma once

#include <cstdlib>
#include <ctime>

inline void InitRandom()
{
    static bool initialised = false;
    if (!initialised)
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        initialised = true;
    }
}

inline float GetRandomFloat(float min, float max)
{
    InitRandom();

    float r = static_cast<float>(std::rand()) / RAND_MAX;
    return min + r * (max - min);
}
