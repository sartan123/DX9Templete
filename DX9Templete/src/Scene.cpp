#include "Scene.h"

Scene::Scene()
:mSquare(nullptr)
, mTriangle(nullptr)
, mMultiTexture(nullptr)
, mParticle(nullptr)
, mInterval(5.5f)
{
}

Scene::~Scene()
{
	Destroy();
}
void Scene::Destroy()
{
	mSquare->Destroy();
	mTriangle->Destroy();
	mTexture->Destroy();
	mMultiTexture->Destroy();
}

HRESULT Scene::Create(LPDIRECT3DDEVICE9 device, HINSTANCE hInstance, HWND hwnd)
{
	mSquare = new Square();
	mSquare->Create(device);

	mTriangle = new TrianglePolygon();
	mTriangle->Create(device);

	mTexture = new BasicTexture();
	mTexture->Create(device);

	mMultiTexture = new MultiTexture();
	mMultiTexture->Create(device);

	mMesh = new MaterialMesh();
	mMesh->Create(device);

	mParticle = new Particle();
	mParticle->Create(device);

	mInput = new InputDevice();
	mInput->Initialize(hInstance, hwnd);

	return S_OK;
}

void Scene::Draw(LPDIRECT3DDEVICE9 device)
{
	//mSquare->Draw(device);

	//mTriangle->Draw(device);

	//mTexture->Draw(device);

	//mMultiTexture->Draw(device);

	UpdateInput();

	mMesh->Draw(device);

	//mParticle->Draw(device);
}

void Scene::UpdateInput()
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