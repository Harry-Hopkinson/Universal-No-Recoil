#include "Recoil.h"

WeaponRecoil CurrentRecoil = { 3.00f, 0.00f };

int ControllerMultiplier = 10;

std::pair<float, float> CalculateRecoil(
    float baseX, float baseY, float lookX, float lookY)
{
    float adjustedX = baseX + (lookX * ControllerMultiplier);
    float adjustedY = baseY + (-lookY * ControllerMultiplier);
    return { adjustedX, adjustedY };
}
