#pragma once

#include "Structs.h"

#include <vector>

extern WeaponRecoil CurrentRecoil;

extern int ControllerMultiplier;

std::pair<float, float> CalculateRecoil(
    float baseX, float baseY, float lookX, float lookY);
