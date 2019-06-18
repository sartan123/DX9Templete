#pragma once
#include "stddef.h"
#include <d3d9.h>
#include <d3dx9.h>

class GameObject
{
public:
	GameObject();
	~GameObject();
	virtual HRESULT Create(LPDIRECT3DDEVICE9 device) = 0;
	virtual void Draw(IDirect3DDevice9* device) = 0;
	virtual void SetWorldMatrix();
	virtual void SetViewMatrix() = 0;
	virtual HRESULT SetProjectionMatrix(IDirect3DDevice9* device);
protected:
	D3DXMATRIX m_world;
	D3DXMATRIX m_world_inv;
	D3DXMATRIX m_projection;
	D3DXMATRIX m_view;

	D3DXMATRIX m_scale;
	D3DXMATRIX m_rotate;
	D3DXMATRIX m_transelate;
};

