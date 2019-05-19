#pragma once
#include <d3d9.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

class App
{
private:
	D3DPRESENT_PARAMETERS	d3dpp;
	IDirect3D9Ex* pD3d;
	IDirect3DDevice9Ex* pDevice;
public:
	template<class T>
	void SafeRelease(T p) {
		if (p)
		{
			p->Release();
			p = nullptr;
		}
	}
	enum ScreenMode
	{
		WindowMode,
		FullScreenMode,
		VirtualFullScreenMode,
	};
	App();
	~App();
	bool Initialize(HWND hwnd, int width, int height, ScreenMode mode);

	void Render();
	void Terminate();
	
};

