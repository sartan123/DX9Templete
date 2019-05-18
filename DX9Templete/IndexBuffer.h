#pragma once
#include "Graphic.h"

#define FVF_CUSTOM2D    (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
struct SimpleVertex
{
	float x, y, z;
	float rhw;
	DWORD color;
};

class IndexBuffer : public Graphic
{
private:
	IDirect3DVertexBuffer9* g_pVertexBuffer;
	IDirect3DIndexBuffer9* g_pIndexBuffer;
	bool InitializeResource();
	IDirect3DIndexBuffer9* CreateIndexBuffer(const UINT16* pIndeces, size_t size);
	IDirect3DVertexBuffer9* CreateVertexBuffer(const void* pVertices, size_t size);
public:
	IndexBuffer(LPDIRECT3DDEVICE9 p);
	~IndexBuffer();
	virtual void Draw();
};

