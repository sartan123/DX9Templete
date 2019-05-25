#pragma once
#include "stddef.h"
#include "Sprite.h"
#include "MaterialMesh.h"
#include "Camera.h"
#include "TextFont.h"
#include "InputDevice.h"
#include "TrianglePolygon.h"
#include <d3d9.h>
#include <d3dx9.h>

#define TIMER_ID 1
#define FREAM_RATE (1000 / 60)

class App
{
private:
	D3DPRESENT_PARAMETERS	d3dpp;
	IDirect3D9Ex* pD3d;
	IDirect3DDevice9Ex* pDevice;

	std::vector<Sprite> mSprites;
	MaterialMesh* mMesh;
	Camera* mCamera;
	TextFont* mTextFont;

	TrianglePolygon* vertex;

	InputDevice* mInput;


	DWORD timeBefore;
	DWORD fps;

	float mInterval;
public:
	enum ScreenMode
	{
		WindowMode,
		FullScreenMode,
		VirtualFullScreenMode,
	};
	App();
	~App();
	bool Initialize(HINSTANCE hInstance, HWND hwnd, int width, int height, ScreenMode mode);

	void Render();
	void Terminate();

	void InitializeResource(HINSTANCE hInstance, HWND hwnd);
	void DrawAllResource();

	void run();

	void UpdateInput();
};

