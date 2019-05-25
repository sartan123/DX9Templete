#include "App.h"

App::App()
: pD3d(nullptr)
, pDevice(nullptr)
, mInput(nullptr)
, timeBefore(0)
, fps(0)
, mInterval(0.5f)
{
	ZeroMemory(&d3dpp, sizeof(d3dpp));
}


App::~App()
{
}

bool App::Initialize(HINSTANCE hInstance, HWND hWnd, int Width, int Height, ScreenMode mode)
{
	try
	{
		HRESULT hr;
		hr = Direct3DCreate9Ex(D3D_SDK_VERSION, &pD3d);
		if (FAILED(hr))
		{
			throw std::runtime_error("failed Direct3DCreate9Ex");
		}
		d3dpp.BackBufferCount = 2;
		d3dpp.BackBufferWidth = Width;
		d3dpp.BackBufferHeight = Height;
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
		d3dpp.hDeviceWindow = hWnd;

		D3DDISPLAYMODEEX dm;
		ZeroMemory(&dm, sizeof(dm));
		dm.Size = sizeof(dm);
		dm.Format = d3dpp.BackBufferFormat;
		dm.Width = d3dpp.BackBufferWidth;
		dm.Height = d3dpp.BackBufferHeight;
		dm.ScanLineOrdering = D3DSCANLINEORDERING_UNKNOWN;

		DWORD flag = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE;

		switch (mode)
		{
		case App::WindowMode:
		case App::VirtualFullScreenMode:
			d3dpp.Windowed = TRUE;
			hr = pD3d->CreateDeviceEx(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				hWnd,
				flag,
				&d3dpp,
				nullptr,
				&pDevice);
			break;
		case App::FullScreenMode:
			d3dpp.Windowed = FALSE;
			d3dpp.FullScreen_RefreshRateInHz = 60;
			dm.RefreshRate = d3dpp.FullScreen_RefreshRateInHz;
			hr = pD3d->CreateDeviceEx(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				hWnd,
				flag,
				&d3dpp,
				&dm,
				&pDevice);
			break;
		default:
			std::runtime_error("Not Found ScreenType");
		}
		if (FAILED(hr))
		{
			throw std::runtime_error("failed CreateDeviceEx");
		}

		InitializeResource(hInstance, hWnd);

	}
	catch (std::runtime_error e)
	{
		MessageBoxA(hWnd, e.what(), "初期化失敗", MB_OK);
		return false;
	}
	return true;
}

void App::Render()
{
	DWORD dwClearFlags = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL;
	DWORD dwClearColor = D3DCOLOR_RGBA(0x00, 0x00, 0xff, 0x00);
	pDevice->Clear(0, nullptr, dwClearFlags, dwClearColor, 1.0f, 0);
	pDevice->BeginScene();

	UpdateInput();

	DrawAllResource();

	pDevice->EndScene();
	pDevice->PresentEx(nullptr, nullptr, nullptr, nullptr, NULL);
}

void App::Terminate()
{
	SafeRelease(pDevice);
	SafeRelease(pD3d);
}

void App::InitializeResource(HINSTANCE hInstance, HWND hwnd)
{
	//mMesh = new MaterialMesh();
	//mMesh->Initialize(pDevice);
	//mSprites.push_back(Sprite());
	//mSprites[0].LoadTexture(pDevice, "sample0003.bmp");

	mCamera = new Camera(pDevice);
	mCamera->SetMatrices();

	mTextFont = new TextFont("Test");
	mTextFont->Initialize(pDevice);

	mInput = new InputDevice();
	mInput->Initialize(hInstance, hwnd);

	vertex = new TrianglePolygon();
	vertex->SetVertexBuffer(pDevice);
	vertex->SetVertexDeclaration(pDevice);
	vertex->LoadShader(pDevice);
}

void App::DrawAllResource()
{
	for (int i = 0; i < mSprites.size(); i++)
	{
		mSprites[i].Draw(pDevice);
	}
	mInput->KeyUpDate();
	//mMesh->Draw(pDevice);
	mCamera->Update();
	mTextFont->Draw();
	vertex->Draw(pDevice);
}

void App::run() {
	++fps;
	if ((GetTickCount() - timeBefore) >= 1000) { 
#ifdef _DEBUG // デバッグ用(デバッガにFSP出す)
		std::stringstream stream;
		stream << fps << " FPS" << std::endl;
		mTextFont->ChangeText(TEXT(stream.str().c_str()));
#endif
		fps = 0;
		timeBefore = GetTickCount();
	}
}

void App::UpdateInput()
{
	if(mInput->GetKey(UP_KEY))
	{
		mCamera->MovePositionY(mInterval);
	}
	else if(mInput->GetKey(DOWN_KEY))
	{
		mCamera->MovePositionY(-mInterval);
	}
	else if (mInput->GetKey(LEFT_KEY))
	{
		mCamera->MovePositionX(mInterval);
	}
	else if (mInput->GetKey(RIGHT_KEY))
	{
		mCamera->MovePositionX(-mInterval);
	}
	else
	{
		mInput->GetMouseState();
		if (mInput->IsClickRightMouse())
		{
			int x = mInput->GetMouseStateX();
			int y = mInput->GetMouseStateY();
			mCamera->MovePositionX(x);
			mCamera->MovePositionY(y);
		}

	}
}