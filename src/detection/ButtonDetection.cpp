#include "../handlers/ButtonHandler.h"

#include "../ui/widgets/Button.h"

#include "../utils/WindowUtils.h"

namespace Detection
{

    bool HandleButtonClick(HWND hwnd, int mouseX, int mouseY)
    {
        for (const auto& btn : Buttons::GetButtons())
        {
            if (btn.Contains(mouseX, mouseY))
            {
                switch (btn.id)
                {
                    case 1:
                        ButtonHandler::HandleToggleRecoil(hwnd);
                        break;
                    case 2:
                        ButtonHandler::HandleToggleKey(hwnd);
                        break;
                    case 3:
                        ButtonHandler::HandleSupportProject(hwnd);
                        break;
                    case 4:
                        ButtonHandler::HandleController(hwnd);
                        break;

                    default:
                        break;
                }

                WindowUtils::InvalidateWindowNoChildren(hwnd);
                return true;
            }
        }
        return false;
    }

} // namespace Detection
