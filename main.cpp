#include <string>
#include <Windows.h>

#include "MainWindow.h"
#include "resource.h"

auto g_lpAppName{ L"GetStarted-CppWin32" };

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    MainWindow win;

    if (!win.Create(g_lpAppName, WS_OVERLAPPEDWINDOW))
        return 0;

    HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCEL_MAIN));

    ShowWindow(win.Window(), nCmdShow);

    MSG msg = { };
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (TranslateAccelerator(win.Window(), hAccel, &msg))
            continue;

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}