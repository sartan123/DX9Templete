#include "InputDevice.h"

InputDevice::InputDevice()
{
}


InputDevice::~InputDevice()
{
}

bool InputDevice::Initialize(HINSTANCE hInst, HWND hWnd)
{
	DirectInput8Create(hInst,DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&pInputInterface, NULL);

	pInputInterface->CreateDevice(GUID_SysKeyboard, &pKeyDevice, NULL);
	pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
	pKeyDevice->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	pKeyDevice->Acquire();
	
	pInputInterface->CreateDevice(GUID_SysMouse, &pMouseDevice, NULL);
	pMouseDevice->SetDataFormat(&c_dfDIMouse);
	pMouseDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;
	pMouseDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);
	pMouseDevice->Acquire();

	return true;
}

void InputDevice::ReleaseDirectInput()
{
	pKeyDevice->Unacquire();
	pKeyDevice->Release();
	pInputInterface->Release();
	pMouseDevice->Release();
}
void InputDevice::KeyUpDate()
{
	BYTE KeyState[256];
	HRESULT hr;

	hr = pKeyDevice->GetDeviceState(256, KeyState);
	if (SUCCEEDED(hr))
	{

		DWORD old = mKeyState.now;

		// キー情報クリア
		mKeyState.now = CLEAR_KEY;

		// 上キー
		if (KeyState[DIK_UP] & 0x80)
		{
			mKeyState.now |= UP_KEY;
		}

		// 下キー
		if (KeyState[DIK_DOWN] & 0x80)
		{
			mKeyState.now |= DOWN_KEY;
		}

		// 左キー
		if (KeyState[DIK_LEFT] & 0x80)
		{
			mKeyState.now |= LEFT_KEY;
		}

		// 右キー
		if (KeyState[DIK_RIGHT] & 0x80)
		{
			mKeyState.now |= RIGHT_KEY;
		}

		// リターンキー
		if (KeyState[DIK_RETURN] & 0x80)
		{
			mKeyState.now |= RETURN_KEY;
		}

		mKeyState.trg = (mKeyState.now & (~old));
		mKeyState.ntrg = (~mKeyState.now) & old;
	}
	else if (hr == DIERR_INPUTLOST) {
		pKeyDevice->Acquire();
	}
}

bool InputDevice::GetKey(DWORD key_code)
{
	return mKeyState.now & key_code;
}

bool InputDevice::GetKeyDown(DWORD key_code)
{
	return mKeyState.trg & key_code;
}

bool InputDevice::GetKeyUp(DWORD key_code)
{
	return mKeyState.ntrg & key_code;
}

void InputDevice::GetMouseState()
{
	DIMOUSESTATE g_zdiMouseState_bak;
	memcpy(&g_zdiMouseState_bak, &mMouseState, sizeof(g_zdiMouseState_bak));

	HRESULT	hr = pMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &mMouseState);
	if (hr == DIERR_INPUTLOST) {
		pMouseDevice->Acquire();
		hr = pMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &mMouseState);
	}

	if (memcmp(&g_zdiMouseState_bak, &mMouseState, sizeof(g_zdiMouseState_bak)) != 0) {
#ifdef _DEBUG
		char buf[128];
		wsprintf(buf, "(%5d, %5d, %5d) %s %s %s\n",
			mMouseState.lX, mMouseState.lY, mMouseState.lZ,
			(mMouseState.rgbButtons[0] & 0x80) ? "Left" : "--",
			(mMouseState.rgbButtons[1] & 0x80) ? "Right" : "--",
			(mMouseState.rgbButtons[2] & 0x80) ? "Center" : "--");
		OutputDebugString(buf);
#endif
	}
}

bool InputDevice::IsClickRightMouse()
{
	return mMouseState.rgbButtons[1] & 0x80;
}

int InputDevice::GetMouseStateX()
{
	return mMouseState.lX;
}
int InputDevice::GetMouseStateY()
{
	return mMouseState.lY;
}