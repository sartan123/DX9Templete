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