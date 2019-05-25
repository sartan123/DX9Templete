#pragma once
#include "stddef.h"
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#define CLEAR_KEY	0x0000
#define UP_KEY		0x0001
#define DOWN_KEY	0x0002
#define LEFT_KEY	0x0004
#define RIGHT_KEY	0x0008
#define RETURN_KEY	0x0010

struct INPUTSTATE
{
	DWORD now;
	DWORD trg;
	DWORD ntrg;
};

class InputDevice
{
private:
	LPDIRECTINPUT8 pInputInterface;
	LPDIRECTINPUTDEVICE8 pKeyDevice;
	LPDIRECTINPUTDEVICE8 pMouseDevice;
	DIMOUSESTATE mMouseState;
	INPUTSTATE mKeyState;
public:
	InputDevice();
	~InputDevice();
	bool Initialize(HINSTANCE instance_handle, HWND window_handle);
	void ReleaseDirectInput();
	void KeyUpDate();
	bool GetKey(DWORD key_code);
	bool GetKeyDown(DWORD key_code);
	bool GetKeyUp(DWORD key_code);

	void GetMouseState();
	bool IsClickRightMouse();
	int GetMouseStateX();
	int GetMouseStateY();
};

