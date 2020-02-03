#include "pch.h"

#include "MainWindow.h"

using namespace std;

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_SIZE:
    {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);
        OutputDebugString((L"width " + std::to_wstring(width) + L", height " + std::to_wstring(height) + L"\n").c_str());
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        EndPaint(m_hwnd, &ps);
        return 0;
    }
    case WM_COMMAND:
        OnCommand(wParam);
        return 0;
    case WM_CLOSE:
    {
        if (MessageBox(m_hwnd, L"Really quit?", m_lpWindowsName, MB_OKCANCEL) == IDOK)
            DestroyWindow(m_hwnd);
        return 0;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    default:
        break;
    }
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

void MainWindow::OnCommand(WPARAM wParam)
{
    switch (LOWORD(wParam))
    {
    case ID_START_SCAN:
        OutputDebugString(L"OnCommand ID_START_SCAN\n");
        bluetoothLEWatcher = BluetoothLEAdvertisementWatcher();
        bluetoothLEWatcherReceivedToken = bluetoothLEWatcher.Received({ this, &MainWindow::BluetoothLEWatcher_Received });
        bluetoothLEWatcher.Start();
        break;
    case ID_STOP_SCAN:
        OutputDebugString(L"OnCommand ID_STOP_SCAN\n");
        if (bluetoothLEWatcher)
        {
            bluetoothLEWatcher.Stop();
            bluetoothLEWatcher.Received(bluetoothLEWatcherReceivedToken);
        }
        bluetoothLEWatcher = nullptr;
        break;
    default:
        break;
    }
}

void MainWindow::BluetoothLEWatcher_Received(BluetoothLEAdvertisementWatcher sender, BluetoothLEAdvertisementReceivedEventArgs args)
{
    OutputDebugString((L"Received " + to_wstring(args.BluetoothAddress()) + L"\n").c_str());
}
