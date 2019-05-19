#include "stddef.h"
#include "App.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
LPCTSTR szAppName = "Direct3D Templete";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		switch ((CHAR)wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

HWND SetupWindow(HINSTANCE hInstance, int width, int height, App::ScreenMode mode)
{
	DWORD dwExStyle = 0;
	DWORD dwStyle;
	RECT rect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };


	int cx = CW_USEDEFAULT, cy = CW_USEDEFAULT;

	switch (mode)
	{
	case App::WindowMode:
		dwStyle = WS_OVERLAPPEDWINDOW & ~(WS_SIZEBOX | WS_MAXIMIZEBOX);
		AdjustWindowRect(&rect, dwStyle, FALSE);
		break;
	case App::FullScreenMode:
		dwStyle = WS_POPUP;
		cx = 0;
		cy = 0;
		break;
	case App::VirtualFullScreenMode:
		dwStyle = WS_POPUP;
		dwExStyle = WS_EX_TOPMOST;
		cx = 0;
		cy = 0;
		break;
	default:
		break;
	}

	HWND hWnd = CreateWindowEx(
		dwExStyle,
		szAppName,
		szAppName,
		dwStyle,
		cx,
		cy,
		rect.right - rect.left,
		rect.bottom - rect.top,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);
	return hWnd;
}

bool EnterVirtualFullScreen(int width, int height)
{
	DEVMODE devMode;
	int nModeIndex = 0;
	while (EnumDisplaySettings(NULL, nModeIndex++, &devMode))
	{
		if (devMode.dmPelsWidth != width || devMode.dmPelsHeight != height)
		{
			continue;
		}
		if (devMode.dmBitsPerPel != 32)
		{
			continue;
		}
		if (devMode.dmDisplayFrequency != 60)
		{
			continue;
		}
		if (ChangeDisplaySettings(&devMode, CDS_TEST) == DISP_CHANGE_SUCCESSFUL)
		{
			ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
			return true;
		}
	}
	return false;
}

void LeaveVirtualFullScreen()
{
	ChangeDisplaySettings(NULL, 0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szStr, INT iCmdShow)
{
	WNDCLASSEX wndClass;
	wndClass.cbSize = sizeof(wndClass);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = szAppName;
	wndClass.hIconSm = LoadIcon(NULL, IDI_ASTERISK);
	if (!RegisterClassEx(&wndClass))
	{
		return -1;
	}

	App::ScreenMode screenMode = App::WindowMode;
	if (App::VirtualFullScreenMode == screenMode)
	{
		EnterVirtualFullScreen(WINDOW_WIDTH, WINDOW_HEIGHT);
	}
	HWND hWnd = SetupWindow(hInstance, WINDOW_WIDTH, WINDOW_HEIGHT, screenMode);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	App app;
	app.Initialize(hWnd, WINDOW_WIDTH, WINDOW_HEIGHT, screenMode);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			app.Render();
		}
	}
	app.Terminate();

	return (INT)msg.wParam;
}
