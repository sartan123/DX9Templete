#pragma once
#include "stddef.h"
#include "GameObject.h"

class MaterialMesh : public GameObject
{
private:
	LPD3DXMESH				m_pMesh;
	LPD3DXBUFFER			m_pD3DXMtrlBuffer;
	DWORD					m_numMtrl;
	LPDIRECT3DTEXTURE9*		m_pTextures;

	float mRotate;

	LPD3DXEFFECT	m_pFX;

	D3DXHANDLE	m_hTech;

	D3DXHANDLE	m_hWorld;
	D3DXHANDLE	m_hWorldInv;
	D3DXHANDLE	m_hView;
	D3DXHANDLE	m_hProj;
	D3DXHANDLE	m_hColor0;
	D3DXHANDLE	m_hColor1;
	D3DXHANDLE	m_hLightDir;
	D3DXHANDLE	m_hTexture;
public:
	MaterialMesh();
	~MaterialMesh();
	virtual HRESULT Create(LPDIRECT3DDEVICE9 device);
	virtual void Draw(IDirect3DDevice9* device);
	virtual HRESULT SetShader(IDirect3DDevice9* device);
	HRESULT LoadMeshFile(LPDIRECT3DDEVICE9 device);
};

