#include "Recoil.h"

#include "../Globals.h"
#include "../core/Random.h"

WeaponRecoil CurrentRecoil = { 5.00f, 0.00f };

float ControllerMultiplier = 10.0f;

std::pair<float, float> CalculateControllerRecoil(float baseX, float baseY, float lookX, float lookY)
{
    float randomX = 0.0f;
    float randomY = 0.0f;

    if (RandomRecoil)
    {
        randomX = GetRandomFloat(-CurrentRecoil.Horizontal, CurrentRecoil.Horizontal);
        randomY = GetRandomFloat(-CurrentRecoil.Vertical, CurrentRecoil.Vertical);
    }

    float adjustedX = baseX + (lookX * ControllerMultiplier) + randomX;
    float adjustedY = baseY + (-lookY * ControllerMultiplier) + randomY;

    return { adjustedX, adjustedY };
}
