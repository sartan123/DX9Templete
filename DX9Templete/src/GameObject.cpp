#include "GameObject.h"

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::SetWorldMatrix()
{
	D3DXMatrixIdentity(&m_world);
	D3DXMatrixIdentity(&m_scale);
	D3DXMatrixIdentity(&m_rotate);
	D3DXMatrixIdentity(&m_transelate);
}

void GameObject::SetViewMatrix()
{
	D3DXMatrixIdentity(&m_view);
	D3DXMatrixLookAtLH(&m_view,
		&D3DXVECTOR3(0.0f, 0.0f, -10.0f),
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));
}

HRESULT GameObject::SetProjectionMatrix(IDirect3DDevice9* device)
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

HRESULT GameObject::SetShader(IDirect3DDevice9* device)
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