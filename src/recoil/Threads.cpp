#include "Threads.h"

#include "../Globals.h"
#include "../core/Keys.h"

#include "../files/Files.h"
#include "../inputs/Inputs.h"
#include "../recoil/Recoil.h"
#include "../utils/StringUtils.h"

inline constexpr int FIRE_DELAY_MS = 5;

inline constexpr int TOGGLE_DELAY_MS = 300;
inline constexpr int POLL_INTERVAL_MS = 50;

inline constexpr const char* WINDOW_TITLE = "Universal No Recoil";

static HWND GetWindowHandle()
{
    static HWND hwnd = nullptr;
    if (!hwnd || !IsWindow(hwnd))
        hwnd = FindWindow(NULL, WINDOW_TITLE);
    return hwnd;
}

DWORD WINAPI WorkerThreadProc(LPVOID)
{
    ULONGLONG lastMoveTime = 0;

    while (Running)
    {
        ULONGLONG now = GetTickCount64();

        const bool controllerConnected = EnableController
            && Inputs::IsControllerConnected();

        const bool isADS = Inputs::IsMouseADS()
            || (controllerConnected
                && Inputs::IsControllerADS(Inputs::GetControllerState()));

        const bool firingMouse = Inputs::IsMouseFiring();
        const bool firingController = controllerConnected
            && Inputs::IsControllerFiring(Inputs::GetControllerState());

        if (EnableRC && isADS && (firingMouse || firingController))
        {
            if (now - lastMoveTime >= FIRE_DELAY_MS)
            {
                float moveX = CurrentRecoil.Horizontal * 2.0f;
                float moveY = CurrentRecoil.Vertical * 2.0f;

                if (controllerConnected)
                {
                    XINPUT_STATE state = Inputs::GetControllerState();
                    float lookX, lookY;
                    Inputs::GetControllerStickInput(state, lookX, lookY);

                    auto [rx, ry] = CalculateRecoil(moveX, moveY, lookX, lookY);
                    moveX = rx;
                    moveY = ry;
                }

                Inputs::MoveMouseRaw(moveX, moveY);
                lastMoveTime = now;
            }

            Sleep(1);
            continue;
        }

        if (UseToggleKey && (GetAsyncKeyState(ToggleKey) & 0x8000))
        {
            EnableRC = !EnableRC;
            Files::SaveConfig();

            if (HWND hwnd = GetWindowHandle())
                InvalidateRect(hwnd, NULL, FALSE);

            Sleep(TOGGLE_DELAY_MS);
        }

        Sleep(POLL_INTERVAL_MS);
    }

    return 0;
}
