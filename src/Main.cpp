#include <windows.h>
#include <windowsx.h>

#include "detection/ButtonDetection.h"
#include "resource/resource.h"

#include "Globals.h"

#include "drawing/Drawing.h"

#include "files/Files.h"

#include "recoil/Recoil.h"
#include "recoil/Threads.h"

#include "ui/Themes.h"
#include "ui/Font.h"
#include "ui/widgets/Button.h"
#include "ui/widgets/Slider.h"

// Window Procedure for handling events
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
        {
            Running = false;
            DestroyWindow(hwnd);
            return 0;
        }
        break;

        case WM_CREATE:
        {
            HICON hIcon = LoadIcon(
                GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
            SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

            Buttons::CreateOperatorSelectionButtons();
            Sliders::CreateSliders();

            Font::CreateFonts();
        }
        break;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT rect;
            GetClientRect(hwnd, &rect);

            HDC memDC = CreateCompatibleDC(hdc);
            HBITMAP memBitmap = CreateCompatibleBitmap(
                hdc, rect.right, rect.bottom);
            HGDIOBJ oldBitmap = SelectObject(memDC, memBitmap);

            HBRUSH bgBrush = CreateSolidBrush(BackgroundColour);
            FillRect(memDC, &rect, bgBrush);
            DeleteObject(bgBrush);

            Drawing::Draw(memDC, rect.right, rect.bottom);

            BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);

            SelectObject(memDC, oldBitmap);
            DeleteObject(memBitmap);
            DeleteDC(memDC);
            EndPaint(hwnd, &ps);
        }
        break;

        case WM_LBUTTONDOWN:
        {
            int mouseX = GET_X_LPARAM(lParam);
            int mouseY = GET_Y_LPARAM(lParam);

            if (Sliders::OnLButtonDown(hwnd, mouseX, mouseY))
                break;

            if (Detection::HandleButtonClick(hwnd, mouseX, mouseY))
                break;
        }
        break;

        case WM_MOUSEMOVE:
        {
            int mouseX = GET_X_LPARAM(lParam);

            if (Sliders::OnMouseMove(hwnd, mouseX))
                break;
        }
        break;

        case WM_LBUTTONUP:
        {
            int mouseX = GET_X_LPARAM(lParam);

            if (Sliders::OnLButtonUp(hwnd, mouseX))
                break;
        }
        break;

        case WM_DESTROY:
        {
            Buttons::ClearButtons();
            Sliders::ClearSliders();

            Font::Cleanup();

            PostQuitMessage(0);
            return 0;
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    WNDCLASS wc = {};
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = "UniversalNoRecoil";
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WindowProc;
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

    RegisterClass(&wc);

    Files::LoadConfig();

    HWND hwnd = CreateWindowEx(
        0, wc.lpszClassName, "Universal No Recoil",
        (WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME)),
        CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, nullptr,
        nullptr, hInstance, nullptr);

    if (!hwnd)
        return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    HANDLE hWorker = CreateThread(
        nullptr, 0, WorkerThreadProc, nullptr, 0, nullptr);

    MSG msg = {};
    while (Running)
    {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE)
            {
                Running = false;
                PostMessage(hwnd, WM_CLOSE, 0, 0);
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        Sleep(16);
    }

    WaitForSingleObject(hWorker, INFINITE);
    CloseHandle(hWorker);

    return 0;
}
