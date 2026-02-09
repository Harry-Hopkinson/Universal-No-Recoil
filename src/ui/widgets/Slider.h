#pragma once

#include <windows.h>

namespace Sliders
{
    struct Slider
    {
        int id;

        int x;
        int y;

        int width;
        int height;

        float min;
        float max;

        float value;
        float step;

        RECT GetRect() const
        {
            return RECT{ x, y, x + width, y + height };
        }
    };

    void CreateSliders();
    void ClearSliders();

    void DrawSliders(HDC memDC);

    bool OnLButtonDown(HWND hwnd, int mouseX, int mouseY);
    bool OnMouseMove(HWND hwnd, int mouseX);
    bool OnLButtonUp(HWND hwnd, int mouseX);

    void SetSliderValue();

} // namespace Sliders
