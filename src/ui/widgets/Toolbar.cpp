#include "Toolbar.h"

#include "../Font.h"
#include "../Themes.h"

#include "../../Globals.h"
#include "../../core/Keys.h"
#include "../../recoil/Recoil.h"

#include <cstdio>

inline constexpr float CURRENT_VERSION = 1.0f;

namespace Toolbar
{

    void DrawToolBar(HDC memDC, int right)
    {
        HFONT oldFont = (HFONT)SelectObject(memDC, Font::GetDescFont());
        SetTextColor(memDC, TextColour);
        SetBkMode(memDC, TRANSPARENT);

        HBRUSH bgBrush = CreateSolidBrush(BackgroundColour);
        HPEN pen = CreatePen(PS_SOLID, 1, LineColour);
        HGDIOBJ oldBrush = SelectObject(memDC, bgBrush);
        HGDIOBJ oldPen = SelectObject(memDC, pen);

        const int padding = 30;
        const int innerPadding = 8;
        RECT infoBoxRect = { padding, 7, right - padding, 40 };

        Rectangle(memDC, infoBoxRect.left, infoBoxRect.top, infoBoxRect.right, infoBoxRect.bottom);

        char items[6][64];
        sprintf_s(items[0], "Status: %s", EnableRC ? "On" : "Off");
        sprintf_s(items[1], "V:%.2f H:%.2f", CurrentRecoil.Vertical, CurrentRecoil.Horizontal);
        sprintf_s(items[2], "Toggle: %s", ToggleKeyEnabled ? "On" : "Off");
        sprintf_s(items[3], "Random: %s", RandomRecoil ? "On" : "Off");
        sprintf_s(items[4], "Controller: %s(%.2f)", EnableController ? "On" : "Off", ControllerMultiplier);
        sprintf_s(items[5], "v%.1f", CURRENT_VERSION);

        // Measure each string's pixel width
        int textWidths[6];
        int totalTextWidth = 0;
        for (int i = 0; i < 6; ++i)
        {
            SIZE sz{};
            GetTextExtentPoint32A(memDC, items[i], (int)strlen(items[i]), &sz);

            textWidths[i] = sz.cx;
            totalTextWidth += sz.cx;
        }

        const int availableWidth = (infoBoxRect.right - infoBoxRect.left) - 2 * innerPadding;
        const int totalGap = availableWidth - totalTextWidth;
        const int gapCount = 7;
        const int gap = totalGap / gapCount;

        const int top = infoBoxRect.top + 5;
        const int bot = infoBoxRect.bottom - 5;
        int curX = infoBoxRect.left + innerPadding + gap;

        for (int i = 0; i < 6; ++i)
        {
            RECT textRect = { curX, top, curX + textWidths[i], bot };
            DrawText(memDC, items[i], -1, &textRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);
            curX += textWidths[i] + gap;
        }

        SelectObject(memDC, oldFont);
        SelectObject(memDC, oldPen);
        SelectObject(memDC, oldBrush);

        DeleteObject(pen);
        DeleteObject(bgBrush);
    }

} // namespace Toolbar
