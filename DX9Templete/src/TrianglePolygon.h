#pragma once
#include "stddef.h"
#include <d3d9.h>
#include <d3dx9.h>

class TrianglePolygon
{
protected:
	D3DXMATRIX m_world;
	D3DXMATRIX m_projection;
	D3DXMATRIX m_view;

	D3DXMATRIX m_scale;
	D3DXMATRIX m_rotate;
	D3DXMATRIX m_transelate;

	float mRotate;

	struct VERTEX_POS {
		D3DXVECTOR3	p;
	};
	struct VERTEX_COLOR {
		D3DXVECTOR4	color;
	};

	LPDIRECT3DVERTEXDECLARATION9 mVertexDec;
	LPDIRECT3DVERTEXBUFFER9	mVertexBuffer;
	LPDIRECT3DVERTEXBUFFER9	mVertexColorBuffer;

	LPD3DXEFFECT	mEffect;
	D3DXHANDLE	mTechHandle;

	D3DXHANDLE	mWorldHandle;
	D3DXHANDLE	mViewingHandle;
	D3DXHANDLE	mProjectionHandle;
	D3DXHANDLE	mColorHandle;

	VERTEX_POS*	mVertexPos;
	VERTEX_COLOR*	mVertexColor;
	UINT	mPrimitiveCount;

public:
	TrianglePolygon();
	~TrianglePolygon();
	void Destroy();
	HRESULT Create(LPDIRECT3DDEVICE9 device);
	virtual void Draw(IDirect3DDevice9* device);
	virtual HRESULT SetPrimitiveInfo(IDirect3DDevice9* device);
	virtual void SetWorldMatrix();
	virtual void SetViewMatrix();
	virtual HRESULT SetProjectionMatrix(IDirect3DDevice9* device);
	virtual HRESULT SetShader(IDirect3DDevice9* device);

	virtual void MovePosition(D3DXVECTOR3 pos);
};

