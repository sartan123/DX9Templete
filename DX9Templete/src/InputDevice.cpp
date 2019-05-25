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
	return true;
}

void InputDevice::ReleaseDirectInput()
{
	pKeyDevice->Unacquire();
	pKeyDevice->Release();
	pInputInterface->Release();
}
void InputDevice::KeyUpDate()
{
	BYTE KeyState[256];
	HRESULT hr;

	hr = pKeyDevice->GetDeviceState(256, KeyState);
	if (SUCCEEDED(hr))
	{

		DWORD old = mInputState.now;

		// キー情報クリア
		mInputState.now = CLEAR_KEY;

		// 上キー
		if (KeyState[DIK_UP] & 0x80)
		{
			mInputState.now |= UP_KEY;
		}

		// 下キー
		if (KeyState[DIK_DOWN] & 0x80)
		{
			mInputState.now |= DOWN_KEY;
		}

		// 左キー
		if (KeyState[DIK_LEFT] & 0x80)
		{
			mInputState.now |= LEFT_KEY;
		}

		// 右キー
		if (KeyState[DIK_RIGHT] & 0x80)
		{
			mInputState.now |= RIGHT_KEY;
		}

		// リターンキー
		if (KeyState[DIK_RETURN] & 0x80)
		{
			mInputState.now |= RETURN_KEY;
		}

		mInputState.trg = (mInputState.now & (~old));
		mInputState.ntrg = (~mInputState.now) & old;
	}
	else if (hr == DIERR_INPUTLOST) {
		pKeyDevice->Acquire();
	}
}

bool InputDevice::GetKey(DWORD key_code)
{
	return mInputState.now & key_code;
}

bool InputDevice::GetKeyDown(DWORD key_code)
{
	return mInputState.trg & key_code;
}

bool InputDevice::GetKeyUp(DWORD key_code)
{
	return mInputState.ntrg & key_code;
}
