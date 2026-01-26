#include "Slider.h"

#include "../../Globals.h"
#include "../../files/Files.h"
#include "../../recoil/Recoil.h"
#include "../Themes.h"

#include <cstdio>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

#define round(x) ((x) < 0 ? (int)((x) - 0.5f) : (int)((x) + 0.5f))

namespace
{

    std::vector<Sliders::Slider> SlidersVector;

    int DraggingID = -1;
    const int THUMB_WIDTH = 12;
    const int TRACK_HEIGHT = 6;

    static float Clamp(float v, float a, float b)
    {
        return min(b, max(a, v));
    }
    static float RoundToStep(float value, float step)
    {
        if (step <= 0.0f)
            return value;

        return round(value / step) * step;
    }

    static float ValueFromMouse(const Sliders::Slider& s, int mouseX)
    {
        int left = s.x + THUMB_WIDTH / 2;
        int right = s.x + s.width - THUMB_WIDTH / 2;

        if (right <= left)
            return s.min;

        float t = float(mouseX - left) / float(right - left);
        t = Clamp(t, 0.0f, 1.0f);

        float val = s.min + t * (s.max - s.min);
        return RoundToStep(val, s.step);
    }

    static int ThumbXForValue(const Sliders::Slider& s)
    {
        float t = (s.value - s.min) / (s.max - s.min);
        t = Clamp(t, 0.0f, 1.0f);

        int left = s.x + THUMB_WIDTH / 2;
        int right = s.x + s.width - THUMB_WIDTH / 2;
        return left + int(t * (right - left));
    }

    static Sliders::Slider* FindSliderById(int id)
    {
        for (auto& sl : SlidersVector)
            if (sl.id == id)
                return &sl;

        return nullptr;
    }

    static bool IsPointInThumb(const Sliders::Slider& s, int mx, int my)
    {
        int tx = ThumbXForValue(s);
        int ty = s.y + s.height / 2;

        RECT r{ tx - THUMB_WIDTH, ty - THUMB_WIDTH, tx + THUMB_WIDTH,
                ty + THUMB_WIDTH };
        return (mx >= r.left && mx <= r.right && my >= r.top && my <= r.bottom);
    }

    static void ApplySliderValueToRecoilAndInvalidate(
        HWND hwnd, const Sliders::Slider& s)
    {
        if (s.id == 100)
        {
            CurrentRecoil.Vertical = s.value;
        }
        else if (s.id == 101)
        {
            CurrentRecoil.Horizontal = s.value;
        }

        InvalidateRect(hwnd, nullptr, FALSE);
    }

} // namespace

namespace Sliders
{

    void CreateSliders()
    {
        SlidersVector.clear();

        int startX = WINDOW_WIDTH - 200 - (350 / 2);
        int startY = (WINDOW_HEIGHT - 90) / 2;

        Slider vertical;
        vertical.id = 100;
        vertical.x = startX + 150;
        vertical.y = startY - 170;
        vertical.width = 200;
        vertical.height = 24;
        vertical.min = 0.0f;
        vertical.max = 20.0f;
        vertical.value = CurrentRecoil.Vertical;
        vertical.step = 0.1f;
        SlidersVector.push_back(vertical);

        Slider horizontal;
        horizontal.id = 101;
        horizontal.x = startX + 150;
        horizontal.y = startY - 120;
        horizontal.width = 200;
        horizontal.height = 24;
        horizontal.min = -10.0f;
        horizontal.max = 10.0f;
        horizontal.value = CurrentRecoil.Horizontal;
        horizontal.step = 0.1f;
        SlidersVector.push_back(horizontal);
    }

    void ClearSliders()
    {
        SlidersVector.clear();
    }

    void DrawSliders(HDC memDC)
    {
        HBRUSH trackBrush = CreateSolidBrush(RGB(60, 60, 60));
        HBRUSH thumbBrush = CreateSolidBrush(RGB(200, 200, 200));
        HPEN pen = CreatePen(PS_SOLID, 1, RGB(30, 30, 30));

        HGDIOBJ oldBrush = SelectObject(memDC, trackBrush);
        HGDIOBJ oldPen = SelectObject(memDC, pen);
        SetTextColor(memDC, TextColour);
        SetBkMode(memDC, TRANSPARENT);

        for (const auto& s : SlidersVector)
        {
            RECT trackRect = { s.x, s.y + (s.height - TRACK_HEIGHT) / 2,
                               s.x + s.width,
                               s.y + (s.height + TRACK_HEIGHT) / 2 };
            FillRect(memDC, &trackRect, trackBrush);

            int tx = ThumbXForValue(s);
            int ty = s.y + s.height / 2;
            RECT thumbRect = { tx - THUMB_WIDTH / 2, ty - THUMB_WIDTH / 2,
                               tx + THUMB_WIDTH / 2, ty + THUMB_WIDTH / 2 };
            SelectObject(memDC, thumbBrush);
            Ellipse(
                memDC, thumbRect.left, thumbRect.top, thumbRect.right,
                thumbRect.bottom);

            char buf[16];
            sprintf_s(buf, "%.2f", s.value);
            RECT textR = { s.x + s.width + 6, s.y, s.x + s.width + 100,
                           s.y + s.height };
            DrawText(
                memDC, buf, -1, &textR, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
        }

        SelectObject(memDC, oldBrush);
        SelectObject(memDC, oldPen);

        DeleteObject(trackBrush);
        DeleteObject(thumbBrush);
        DeleteObject(pen);
    }

    bool OnLButtonDown(HWND hwnd, int mouseX, int mouseY)
    {
        for (auto& s : SlidersVector)
        {
            RECT r = s.GetRect();
            if (mouseX >= r.left && mouseX <= r.right && mouseY >= r.top
                && mouseY <= r.bottom)
            {
                s.value = ValueFromMouse(s, mouseX);
                ApplySliderValueToRecoilAndInvalidate(hwnd, s);

                DraggingID = s.id;
                SetCapture(hwnd);
                return true;
            }

            if (IsPointInThumb(s, mouseX, mouseY))
            {
                s.value = ValueFromMouse(s, mouseX);
                ApplySliderValueToRecoilAndInvalidate(hwnd, s);

                DraggingID = s.id;
                SetCapture(hwnd);
                return true;
            }
        }
        return false;
    }

    bool OnMouseMove(HWND hwnd, int mouseX, int mouseY, bool leftButtonDown)
    {
        if (DraggingID == -1)
            return false;

        Slider* s = FindSliderById(DraggingID);
        if (!s)
            return false;

        s->value = ValueFromMouse(*s, mouseX);
        ApplySliderValueToRecoilAndInvalidate(hwnd, *s);

        return true;
    }

    bool OnLButtonUp(HWND hwnd, int mouseX, int mouseY)
    {
        if (DraggingID == -1)
            return false;

        Slider* s = FindSliderById(DraggingID);
        if (s)
        {
            s->value = ValueFromMouse(*s, mouseX);
            ApplySliderValueToRecoilAndInvalidate(hwnd, *s);

            Files::SaveConfig();
        }

        DraggingID = -1;
        ReleaseCapture();

        return true;
    }

} // namespace Sliders
