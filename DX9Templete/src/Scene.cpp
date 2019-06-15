#include "Scene.h"

Scene::Scene()
: mVertexBuffer(0)
, mEffect(0)
, mVertexDec(0)
{
}

Scene::~Scene()
{
	Destroy();
}
void Scene::Destroy()
{
	SafeRelease(mVertexBuffer);
	SafeRelease(mEffect);
	SafeRelease(mVertexDec);
}

HRESULT Scene::Create(LPDIRECT3DDEVICE9 device)
{
	Destroy();

	if (device == nullptr)
	{
		return E_FAIL;
	}

	D3DVERTEXELEMENT9 vertex_elements[] = 
	{
		{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{1, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
		D3DDECL_END()
	};

	device->CreateVertexDeclaration(vertex_elements, &mVertexDec);

	if (FAILED(device->CreateVertexBuffer(4 * sizeof(VERTEX_POS), D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &mVertexBuffer, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_POS* pos;
	mVertexBuffer->Lock(0, 0, (void**)&pos, 0);
	pos[0].p = D3DXVECTOR3(-1.5f,  1.5f, 0.0f);
	pos[1].p = D3DXVECTOR3( 1.5f,  1.5f, 0.0f);
	pos[2].p = D3DXVECTOR3(-1.5f, -1.5f, 0.0f);
	pos[3].p = D3DXVECTOR3( 1.5f, -1.5f, 0.0f);
	mVertexBuffer->Unlock();

	if (FAILED(device->CreateVertexBuffer(4 * sizeof(VERTEX_COLOR), D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &mVertexColorBuffer, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_COLOR* color;
	mVertexColorBuffer->Lock(0, 0, (void**)&color, 0);
	color[0].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	color[1].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	color[2].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	color[3].color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	mVertexColorBuffer->Unlock();

	D3DVIEWPORT9 vp;
	if (FAILED(device->GetViewport(&vp)))
	{
		return E_FAIL;
	}

	float aspect;
	aspect = (float)vp.Width / (float)vp.Height;

	D3DXMatrixIdentity(&mProjection);
	D3DXMatrixPerspectiveFovLH(&mProjection, D3DXToRadian(45.0), aspect, 1.0f, 1000.0f);

	D3DXMatrixIdentity(&mView);
	D3DXMatrixLookAtLH(&mView,
		&D3DXVECTOR3(0.0f, 0.0f, -6.0f),
		&D3DXVECTOR3(0.0f, 0.0f,  0.0f),
		&D3DXVECTOR3(0.0f, 1.0f,  0.0f));

	HRESULT hr;
	LPD3DXBUFFER errors = 0;
	std::string file_path = GetStringExecutionDirectory() + "\\" +std::string("basic.fx");
	hr = D3DXCreateEffectFromFile(device, file_path.c_str(), 0, 0, D3DXSHADER_DEBUG, 0, &mEffect, &errors);
	if (hr)
	{
		return E_FAIL;
	}
	if (errors)
	{
		return E_FAIL;
	}

	mTechHandle = mEffect->GetTechniqueByName("BasicTech");
	mWvpHandle = mEffect->GetParameterByName(0, "g_wvp");
	mColorHandle = mEffect->GetParameterByName(0, "g_color");

	return S_OK;
}

void Scene::Draw(LPDIRECT3DDEVICE9 device)
{
	if (device == 0)
	{
		return;
	}
	if (mVertexBuffer == 0)
	{
		return;
	}

	device->SetVertexDeclaration(mVertexDec);
	device->SetStreamSource(0, mVertexBuffer, 0, sizeof(VERTEX_POS));
	device->SetStreamSource(1, mVertexColorBuffer, 0, sizeof(VERTEX_COLOR));

	mEffect->SetTechnique(mTechHandle);
	mEffect->SetMatrix(mWvpHandle, &(mView*mProjection));
	//mEffect->SetVector(mColorHandle, &color);
	mEffect->CommitChanges();

	mEffect->Begin(0, 0);
	mEffect->BeginPass(0);

	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	mEffect->EndPass();
	mEffect->End();
}
