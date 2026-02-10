#include "../ui/Themes.h"
#include "../ui/Font.h"

#include "../ui/widgets/Button.h"
#include "../ui/widgets/Slider.h"
#include "../ui/widgets/Toolbar.h"

namespace Drawing
{

    static void DrawButton(HDC memDC, const Button& btn)
    {
        HBRUSH bgBrush = CreateSolidBrush(ButtonColour);
        HPEN pen = CreatePen(PS_SOLID, 1, LineColour);
        HGDIOBJ oldBrush = SelectObject(memDC, bgBrush);
        HGDIOBJ oldPen = SelectObject(memDC, pen);

        RoundRect(
            memDC, btn.x, btn.y, btn.x + btn.width, btn.y + btn.height, 6, 6);

        SelectObject(memDC, oldBrush);
        SelectObject(memDC, oldPen);
        DeleteObject(bgBrush);
        DeleteObject(pen);

        SetTextColor(memDC, TextColour);
        SetBkMode(memDC, TRANSPARENT);
        RECT textRect = btn.GetRect();
        DrawText(
            memDC, btn.text, -1, &textRect,
            DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    void Draw(HDC memDC, int right, int bottom)
    {
        HPEN pen = CreatePen(PS_SOLID, 1, LineColour);
        HGDIOBJ oldPen = SelectObject(memDC, pen);

        HFONT oldFont = (HFONT)SelectObject(memDC, Font::GetDescFont());
        SetTextColor(memDC, TextColour);
        SetBkMode(memDC, TRANSPARENT);

        Toolbar::DrawToolBar(memDC, right);

        const int panelLeft = 20;
        const int panelWidth = 360;
        const int panelTop = (bottom - 160) / 2;
        RECT panelRect = { panelLeft, panelTop, panelLeft + panelWidth,
                           panelTop + 160 };

        HBRUSH panelBrush = CreateSolidBrush(RGB(32, 32, 32));
        HGDIOBJ oldBrush = SelectObject(memDC, panelBrush);
        Rectangle(
            memDC, panelRect.left, panelRect.top, panelRect.right,
            panelRect.bottom);
        SelectObject(memDC, oldBrush);
        DeleteObject(panelBrush);

        for (const auto& btn : Buttons::GetButtons())
            DrawButton(memDC, btn);

        // Vertical separator
        int lineX = panelRect.right + 12;
        MoveToEx(memDC, lineX, 60, nullptr);
        LineTo(memDC, lineX, bottom - 20);

        // Labels to the right of the separator, before sliders
        int labelLeft = lineX + 12;
        int labelRight = labelLeft + 180;
        RECT verticalLabelRect = { labelLeft, panelTop + 10, labelRight,
                                   panelTop + 30 };
        RECT horizontalLabelRect = { labelLeft, panelTop + 40, labelRight,
                                     panelTop + 60 };
        DrawText(
            memDC, "Vertical Recoil:", -1, &verticalLabelRect,
            DT_LEFT | DT_SINGLELINE | DT_VCENTER);
        DrawText(
            memDC, "Horizontal Recoil:", -1, &horizontalLabelRect,
            DT_LEFT | DT_SINGLELINE | DT_VCENTER);

        Sliders::DrawSliders(memDC);

        SelectObject(memDC, oldFont);
        SelectObject(memDC, oldPen);
        DeleteObject(pen);
    }

} // namespace Drawing
