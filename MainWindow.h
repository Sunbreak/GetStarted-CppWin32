#pragma once
#include "BaseWindow.h"

using namespace winrt;
using namespace Windows::Devices::Bluetooth::Advertisement;

class MainWindow : public BaseWindow<MainWindow>
{
public:
    PCWSTR ClassName() const { return L"MainWindow"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
    void OnCommand(WPARAM wParam);

    BluetoothLEAdvertisementWatcher bluetoothLEWatcher{ nullptr };
    event_token bluetoothLEWatcherReceivedToken;
    void BluetoothLEWatcher_Received(BluetoothLEAdvertisementWatcher sender, BluetoothLEAdvertisementReceivedEventArgs args);
};
