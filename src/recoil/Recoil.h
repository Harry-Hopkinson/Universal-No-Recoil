#pragma once

#include <vector>

struct WeaponRecoil
{
    float Vertical;
    float Horizontal;
};

extern WeaponRecoil CurrentRecoil;

extern int ControllerMultiplier;

std::pair<float, float> CalculateRecoil(
    float baseX, float baseY, float lookX, float lookY);
