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
	virtual void SetViewMatrix();
	virtual HRESULT SetProjectionMatrix(IDirect3DDevice9* device);
	virtual HRESULT SetShader(IDirect3DDevice9* device);
protected:
	D3DXMATRIX m_world;
	D3DXMATRIX m_world_inv;
	D3DXMATRIX m_projection;
	D3DXMATRIX m_view;

	D3DXMATRIX m_scale;
	D3DXMATRIX m_rotate;
	D3DXMATRIX m_transelate;

	LPD3DXEFFECT	mEffect;
	D3DXHANDLE	mTechHandle;

	D3DXHANDLE	mWorldHandle;
	D3DXHANDLE	mViewingHandle;
	D3DXHANDLE	mProjectionHandle;
};

