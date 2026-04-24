#pragma once

typedef struct HWND__* HWND;

namespace ButtonHandler
{

    void HandleToggleRecoil(HWND hwnd);
    void HandleToggleKey(HWND hwnd);

    void HandleSupportProject(HWND hwnd);

    void HandleController(HWND hwnd);

    void HandleRandomisedRecoil(HWND hwnd);

} // namespace ButtonHandler
