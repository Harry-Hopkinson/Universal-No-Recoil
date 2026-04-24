#include "Inputs.h"

#include <windows.h>

#include "../Globals.h"
#include "../recoil/Recoil.h"

namespace Inputs
{

    bool IsMouseADS()
    {
        return (GetAsyncKeyState(VK_RBUTTON) & 0x8000);
    }

    bool IsMouseFiring()
    {
        return (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
    }

    void MoveMouseRaw(float dx, float dy)
    {
        static float accumX = 0.0f;
        static float accumY = 0.0f;

        accumX += dx;
        accumY += dy;

        if (RandomRecoil)
        {
            float randomX = (static_cast<float>(rand()) / RAND_MAX) * 2.0f - 1.0f;
            float randomY = (static_cast<float>(rand()) / RAND_MAX) * 2.0f - 1.0f;
            accumX += randomX * CurrentRecoil.Horizontal;
            accumY += randomY * CurrentRecoil.Vertical;
        }

        LONG moveX = static_cast<LONG>(accumX);
        LONG moveY = static_cast<LONG>(accumY);

        if (moveX != 0 || moveY != 0)
        {
            INPUT input = { 0 };
            input.type = INPUT_MOUSE;
            input.mi.dx = moveX;
            input.mi.dy = moveY;
            input.mi.dwFlags = MOUSEEVENTF_MOVE;
            SendInput(1, &input, sizeof(INPUT));

            accumX -= moveX;
            accumY -= moveY;
        }
    }

} // namespace Inputs
