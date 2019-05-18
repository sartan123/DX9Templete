#include "DirectX.h"

DirectX::DirectX(HWND hWnd)
: pD3d(NULL)
, pDevice(NULL)
{
	mGraphics.clear();
	if (FAILED(InitD3d(hWnd)))
	{
		throw std::runtime_error("Failed Create DreictX");
	}
}


DirectX::~DirectX()
{
	SAFE_RELEASE(pDevice);
	SAFE_RELEASE(pD3d);
}

HRESULT DirectX::InitD3d(HWND hWnd)
{
	pD3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (pD3d == NULL)
	{
		MessageBox(0, "DirectX3D‚Ìì¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½", "", MB_OK);
		return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;

	if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &pDevice)))
	{
		if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDevice)))
		{
			if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &pDevice)))
			{
				if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDevice)))
				{
					MessageBox(0, "Direct3DƒfƒoƒCƒX‚Ìì¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½", "", MB_OK);
					return E_FAIL;

				}
			}
		}
	}

	SetGraphic();

	return S_OK;
}

void DirectX::Render()
{
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	pDevice->BeginScene();

	for (int i = 0; i < mGraphics.size(); i++)
	{
		mGraphics[i].Draw();
	}

	pDevice->EndScene();
	pDevice->Present(NULL, NULL, NULL, NULL);
}

void DirectX::SetGraphic()
{
	mGraphics.push_back(Graphic(pDevice));
}