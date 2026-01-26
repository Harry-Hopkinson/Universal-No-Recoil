#include "../ui/Bitmap.h"
#include "../ui/Themes.h"
#include "../ui/Font.h"

#include "../ui/widgets/Button.h"
#include "../ui/widgets/Slider.h"
#include "../ui/widgets/Toolbar.h"

#include "../utils/LayoutUtils.h"

namespace Drawing
{

    static void DrawButton(HDC memDC, const Button& btn)
    {
        HBRUSH bgBrush = CreateSolidBrush(ButtonColour);
        HPEN pen = CreatePen(PS_SOLID, 1, LineColour);
        HGDIOBJ oldBrush = SelectObject(memDC, bgBrush);
        HGDIOBJ oldPen = SelectObject(memDC, pen);

        Rectangle(memDC, btn.x, btn.y, btn.x + btn.width, btn.y + btn.height);

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

    void DrawOperatorSelection(HDC memDC, int right, int bottom)
    {
        const auto& bitmaps = Bitmap::GetCurrentBitmapList();

        HPEN pen = CreatePen(PS_SOLID, 1, LineColour);
        HGDIOBJ oldPen = SelectObject(memDC, pen);

        HFONT oldFont = (HFONT)SelectObject(memDC, Font::GetDescFont());
        SetTextColor(memDC, TextColour);

        SetBkMode(memDC, TRANSPARENT);

        int cellSize = LayoutUtils::OperatorGridLayout::GetCellSize(
            right, bottom);

        for (size_t i = 0; i < bitmaps.size(); ++i)
        {
            int x, y;
            LayoutUtils::OperatorGridLayout::GetCellPosition(
                i, right, bottom, x, y);

            Bitmap::DrawBitmap(memDC, bitmaps[i], x, y, cellSize, cellSize, 45);
        }

        Toolbar::DrawToolBar(memDC, right, bottom);

        Sliders::DrawSliders(memDC);

        // Draw all buttons
        for (const auto& btn : Buttons::GetButtons())
            DrawButton(memDC, btn);

        // Draw vertical line
        int lineX = static_cast<int>(right * 0.66f);
        MoveToEx(memDC, lineX, 60, nullptr);
        LineTo(memDC, lineX, bottom - 20);

        // Cleanup
        SelectObject(memDC, oldFont);
        SelectObject(memDC, oldPen);

        DeleteObject(pen);
    }

} // namespace Drawing
