#include "ButtonHandler.h"

#include <windows.h>

#include "../Globals.h"

#include "../files/Files.h"

#include "../recoil/Recoil.h"
#include "../scenes/Scenes.h"

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

    void HandleSwitchToAttackers(HWND hwnd)
    {
        IsAttackerView = true;
        Scenes::ChangeCurrentScene(SceneType::OperatorSelection);
        Buttons::CreateOperatorSelectionButtons();

        WindowUtils::InvalidateWindow(hwnd);
    }

    void HandleSwitchToDefenders(HWND hwnd)
    {
        IsAttackerView = false;
        Scenes::ChangeCurrentScene(SceneType::OperatorSelection);

        Buttons::CreateOperatorSelectionButtons();
        WindowUtils::InvalidateWindow(hwnd);
    }

    void HandleSupportProject(HWND)
    {
        system("start https://ko-fi.com/harryhopkinson");
    }

    void HandleJoinDiscord(HWND)
    {
        system("start https://ko-fi.com/harryhopkinson");
    }

    void HandleSavePreset(HWND hwnd)
    {
        Files::SaveWeaponData(PresetIndex);

        WindowUtils::InvalidateWindow(hwnd);
    }

    void HandleUpdateTool(HWND hwnd)
    {
        system("start UpdateTool.bat");

        WindowUtils::InvalidateWindow(hwnd);
    }

    void HandleController(HWND hwnd)
    {
        EnableController = !EnableController;
        Files::SaveConfig();

        Buttons::CreateOperatorSelectionButtons();
        WindowUtils::InvalidateWindow(hwnd);
    }

} // namespace ButtonHandler
