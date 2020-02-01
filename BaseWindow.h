#pragma once
#include <Windows.h>

template <typename T>
class BaseWindow
{
public:
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		T* pThis;
		if (uMsg == WM_CREATE)
		{
			pThis = (T*)(((CREATESTRUCT*)lParam)->lpCreateParams);
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
			pThis->m_hwnd = hwnd;
		}
		else
		{
			pThis = (T*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		}

		return pThis != nullptr ? pThis->HandleMessage(uMsg, wParam, lParam) : DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	BaseWindow() : m_hwnd(nullptr), m_lpWindowsName(nullptr) { }

	bool Create(
		PCWSTR lpWindowName,
		DWORD dwStyle,
		DWORD dwExtStyle = 0,
		int x = CW_USEDEFAULT,
		int y = CW_USEDEFAULT,
		int nWidth = CW_USEDEFAULT,
		int nHeight = CW_USEDEFAULT,
		HWND hWndParent = 0,
		HMENU hMenu = 0
	)
	{
		WNDCLASS wc = { 0 };
		wc.lpfnWndProc = T::WndProc;
		wc.hInstance = GetModuleHandle(nullptr);
		wc.lpszClassName = ClassName();

		RegisterClass(&wc);

		m_hwnd = CreateWindowEx(
			dwExtStyle,
			ClassName(),
			lpWindowName,
			dwStyle,
			x, y, nWidth, nHeight,
			nullptr,
			hMenu,
			GetModuleHandle(nullptr),
			this
		);

		return m_hwnd != nullptr;
	}
	
	HWND Window() const { return m_hwnd; }

protected:
	HWND m_hwnd;
	PCWSTR m_lpWindowsName;

	virtual PCWSTR ClassName() const = 0;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
};
