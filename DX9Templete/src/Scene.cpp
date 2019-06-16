#include "Scene.h"

Scene::Scene()
:mSquare(nullptr)
, mTriangle(nullptr)
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
}

HRESULT Scene::Create(LPDIRECT3DDEVICE9 device)
{
	mSquare = new Square();
	mSquare->Create(device);

	mTriangle = new TrianglePolygon();
	mTriangle->Create(device);

	mTexture = new BasicTexture();
	mTexture->Create(device);

	return S_OK;
}

void Scene::Draw(LPDIRECT3DDEVICE9 device)
{
	//mSquare->Draw(device);

	//mTriangle->Draw(device);

	mTexture->Draw(device);
}
