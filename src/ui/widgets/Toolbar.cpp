#include "Toolbar.h"

#include "../Font.h"
#include "../Themes.h"
#include "../../Globals.h"
#include "../../recoil/Recoil.h"

#include <cstdio>

inline constexpr float CURRENT_VERSION = 3.1f;

namespace Toolbar
{

    void DrawToolBar(HDC memDC, int right, int bottom)
    {
        HFONT oldFont = (HFONT)SelectObject(memDC, Font::GetDescFont());
        SetTextColor(memDC, TextColour);
        SetBkMode(memDC, TRANSPARENT);

        HBRUSH bgBrush = CreateSolidBrush(BackgroundColour);
        HPEN pen = CreatePen(PS_SOLID, 1, LineColour);

        HGDIOBJ oldBrush = SelectObject(memDC, bgBrush);
        HGDIOBJ oldPen = SelectObject(memDC, pen);

        const int padding = 30;
        const int innerPadding = 10;
        RECT infoBoxRect = { padding, 10, right - padding, 40 };

        Rectangle(
            memDC, infoBoxRect.left, infoBoxRect.top, infoBoxRect.right,
            infoBoxRect.bottom);

        const int totalWidth = infoBoxRect.right - infoBoxRect.left;
        const int sectionWidth = totalWidth / 5;
        RECT textRect;

        // Status
        textRect = { infoBoxRect.left + innerPadding, infoBoxRect.top + 5,
                     infoBoxRect.left + sectionWidth - innerPadding,
                     infoBoxRect.bottom - 5 };
        char statusText[50];
        sprintf_s(statusText, "Status: %s", EnableRC ? "Enabled" : "Disabled");
        DrawText(
            memDC, statusText, -1, &textRect,
            DT_LEFT | DT_VCENTER | DT_SINGLELINE);

        // Recoil
        textRect = { infoBoxRect.left + sectionWidth + innerPadding,
                     infoBoxRect.top + 5,
                     infoBoxRect.left + 2 * sectionWidth - innerPadding,
                     infoBoxRect.bottom - 5 };
        char recoilText[60];
        sprintf_s(
            recoilText, sizeof(recoilText), "Recoil: V: %.2f  H: %.2f",
            CurrentRecoil.Vertical, CurrentRecoil.Horizontal);
        DrawText(
            memDC, recoilText, -1, &textRect,
            DT_LEFT | DT_VCENTER | DT_SINGLELINE);

        // Toggle Key
        textRect = { infoBoxRect.left + 2 * sectionWidth + innerPadding,
                     infoBoxRect.top + 5,
                     infoBoxRect.left + 3 * sectionWidth - innerPadding,
                     infoBoxRect.bottom - 5 };
        char toggleText[50];
        sprintf_s(toggleText, "Toggle: %s", UseToggleKey ? "On" : "Off");
        DrawText(
            memDC, toggleText, -1, &textRect,
            DT_LEFT | DT_VCENTER | DT_SINGLELINE);

        // Version
        textRect = { infoBoxRect.left + 4 * sectionWidth + innerPadding,
                     infoBoxRect.top + 5,
                     infoBoxRect.left + 5 * sectionWidth - innerPadding,
                     infoBoxRect.bottom - 5 };
        char versionText[30];
        sprintf_s(versionText, "Version %.1f", CURRENT_VERSION);
        DrawText(
            memDC, versionText, -1, &textRect,
            DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

        // Recoil
        RECT verticalLabelRect = { right - 340, (bottom - 90) / 2 - 140,
                                   right - 150, (bottom - 90) / 2 - 120 };
        RECT horizontalLabelRect = { right - 355, (bottom - 90) / 2 - 90,
                                     right - 150, (bottom - 90) / 2 - 70 };
        DrawText(
            memDC, "Vertical Recoil:", -1, &verticalLabelRect,
            DT_LEFT | DT_SINGLELINE | DT_VCENTER);
        DrawText(
            memDC, "Horizontal Recoil:", -1, &horizontalLabelRect,
            DT_LEFT | DT_SINGLELINE | DT_VCENTER);

        SelectObject(memDC, oldFont);
        SelectObject(memDC, oldPen);
        SelectObject(memDC, oldBrush);

        DeleteObject(pen);
        DeleteObject(bgBrush);
    }

} // namespace Toolbar
