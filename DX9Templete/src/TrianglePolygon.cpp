#include "TrianglePolygon.h"

TrianglePolygon::TrianglePolygon()
: mVertexBuffer(0)
, mEffect(0)
, mVertexDec(0)
, mPrimitiveCount(0)
, mRotate(0)
{
}


TrianglePolygon::~TrianglePolygon()
{
}

void TrianglePolygon::Destroy()
{
	SafeRelease(mVertexBuffer);
	SafeRelease(mEffect);
	SafeRelease(mVertexDec);
}

HRESULT TrianglePolygon::Create(LPDIRECT3DDEVICE9 device)
{
	D3DVERTEXELEMENT9 vertex_elements[] =
	{
		{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{1, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
		D3DDECL_END()
	};

	device->CreateVertexDeclaration(vertex_elements, &mVertexDec);

	SetWorldMatrix();

	SetPrimitiveInfo(device);

	if (FAILED(SetProjectionMatrix(device)))
	{
		return E_FAIL;
	}

	SetViewMatrix();

	if (FAILED(SetShader(device)))
	{
		return E_FAIL;
	}

	return S_OK;
}

void TrianglePolygon::SetWorldMatrix()
{
	D3DXMatrixIdentity(&m_world);
	D3DXMatrixIdentity(&m_scale);
	D3DXMatrixIdentity(&m_rotate);
	D3DXMatrixIdentity(&m_transelate);
}

void TrianglePolygon::SetViewMatrix()
{
	D3DXMatrixIdentity(&m_view);
	D3DXMatrixLookAtLH(&m_view,
		&D3DXVECTOR3(0.0f, 0.0f, -10.0f),
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));
}

HRESULT TrianglePolygon::SetProjectionMatrix(IDirect3DDevice9* device)
{
	D3DVIEWPORT9 vp;
	if (FAILED(device->GetViewport(&vp)))
	{
		return E_FAIL;
	}

	float aspect;
	aspect = (float)vp.Width / (float)vp.Height;

	D3DXMatrixIdentity(&m_projection);
	D3DXMatrixPerspectiveFovLH(&m_projection, D3DXToRadian(45.0), aspect, 1.0f, 1000.0f);

	return S_OK;
}

HRESULT TrianglePolygon::SetShader(IDirect3DDevice9* device)
{
	HRESULT hr;
	LPD3DXBUFFER errors = 0;
	std::string file_path = std::string("..\\DX9Templete\\resource\\Shader\\basic.fx");
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
	mWorldHandle = mEffect->GetParameterByName(0, "g_world");
	mViewingHandle = mEffect->GetParameterByName(0, "g_viewing");
	mProjectionHandle = mEffect->GetParameterByName(0, "g_projection");

	return S_OK;
}

void TrianglePolygon::Draw(IDirect3DDevice9* device)
{
	if (device == 0)
	{
		return;
	}
	if (mVertexBuffer == 0)
	{
		return;
	}

	mRotate += 1.5;
	D3DXMatrixRotationY(&m_rotate, D3DXToRadian(mRotate));
	D3DXMatrixTranslation(&m_transelate, -2.0f, -2.0f, 0.0f);

	m_world = m_scale * m_rotate * m_transelate;

	device->SetVertexDeclaration(mVertexDec);
	device->SetStreamSource(0, mVertexBuffer, 0, sizeof(VERTEX_POS));
	device->SetStreamSource(1, mVertexColorBuffer, 0, sizeof(VERTEX_COLOR));

	mEffect->SetTechnique(mTechHandle);
	mEffect->SetMatrix(mWorldHandle, &(m_world));
	mEffect->SetMatrix(mViewingHandle, &(m_view));
	mEffect->SetMatrix(mProjectionHandle, &(m_projection));
	mEffect->CommitChanges();

	mEffect->Begin(0, 0);
	mEffect->BeginPass(0);

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	mEffect->EndPass();
	mEffect->End();
}

HRESULT TrianglePolygon::SetPrimitiveInfo(IDirect3DDevice9* device)
{
	mPrimitiveCount = 3;

	if (FAILED(device->CreateVertexBuffer(mPrimitiveCount * sizeof(VERTEX_POS), D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &mVertexBuffer, NULL)))
	{
		return E_FAIL;
	}

	mVertexBuffer->Lock(0, 0, (void**)&mVertexPos, 0);
	mVertexPos[0].p = D3DXVECTOR3(-1.5f, 1.5f, 0.0f);
	mVertexPos[1].p = D3DXVECTOR3(1.5f, 1.5f, 0.0f);
	mVertexPos[2].p = D3DXVECTOR3(-1.5f, -1.5f, 0.0f);
	mVertexBuffer->Unlock();

	if (FAILED(device->CreateVertexBuffer(mPrimitiveCount * sizeof(VERTEX_COLOR), D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &mVertexColorBuffer, NULL)))
	{
		return E_FAIL;
	}
	mVertexColorBuffer->Lock(0, 0, (void**)&mVertexColor, 0);
	mVertexColor[0].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	mVertexColor[1].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	mVertexColor[2].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	mVertexColorBuffer->Unlock();

	return S_OK;
}

void TrianglePolygon::MovePosition(D3DXVECTOR3 pos)
{
	D3DXMatrixTranslation(&m_transelate, pos.x, pos.y, pos.z);
	m_world = m_scale * m_rotate * m_transelate;
}