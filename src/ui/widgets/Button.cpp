#include "Button.h"

#include "../../Globals.h"

namespace
{
    std::vector<Button> ButtonsVector;
}

namespace Buttons
{

    std::vector<Button>& GetButtons()
    {
        return ButtonsVector;
    }

    void ClearButtons()
    {
        ButtonsVector.clear();
    }

    void CreateOperatorSelectionButtons()
    {
        ClearButtons();

        int startX = 20;
        int startY = (WINDOW_HEIGHT - 130) / 2;

        ButtonsVector.push_back(
            { 1, startX + 10, startY, 160, 42, "Toggle Recoil" });
        ButtonsVector.push_back(
            { 2, startX + 190, startY, 160, 42, "Toggle Key" });

        ButtonsVector.push_back(
            { 3, startX + 10, startY + 52, 160, 42, "Support the Project" });
        ButtonsVector.push_back(
            { 4, startX + 190, startY + 52, 160, 42,
              EnableController ? "Disable Controller" : "Enable Controller" });
    }

} // namespace Buttons
