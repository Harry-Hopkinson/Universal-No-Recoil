#pragma once

#include <vector>

struct WeaponRecoil
{
    float Vertical;
    float Horizontal;
};

extern WeaponRecoil CurrentRecoil;

extern float ControllerMultiplier;

std::pair<float, float> CalculateControllerRecoil(float baseX, float baseY, float lookX, float lookY);
