#include "ButtonHandler.h"

#include <windows.h>

#include "../Globals.h"

#include "../files/Files.h"

#include "../ui/widgets/Button.h"

#include "../utils/WindowUtils.h"

namespace ButtonHandler
{

    void HandleToggleRecoil(HWND hwnd)
    {
        EnableRC = !EnableRC;
        Files::SaveConfig();

        WindowUtils::InvalidateWindow(hwnd);
    }

    void HandleToggleKey(HWND hwnd)
    {
        UseToggleKey = !UseToggleKey;
        Files::SaveConfig();

        WindowUtils::InvalidateWindow(hwnd);
    }

    void HandleSupportProject(HWND)
    {
        system("start https://ko-fi.com/harryhopkinson");
    }

    void HandleController(HWND hwnd)
    {
        EnableController = !EnableController;
        Files::SaveConfig();

        Buttons::CreateOperatorSelectionButtons();
        WindowUtils::InvalidateWindow(hwnd);
    }

} // namespace ButtonHandler
