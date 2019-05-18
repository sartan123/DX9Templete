#pragma once
#include "stddef.h"
#include "Graphic.h"

class DirectX
{
private:
	LPDIRECT3D9 pD3d;
	LPDIRECT3DDEVICE9 pDevice;
	std::vector<Graphic> mGraphics;
public:
	DirectX(HWND hWnd);
	~DirectX();
	HRESULT InitD3d(HWND hWnd);
	LPDIRECT3D9 GetDirect3D9() { return pD3d;  }
	LPDIRECT3DDEVICE9 GetDirectDevice() { return pDevice; }

	void Render();
	void SetGraphic();
};

