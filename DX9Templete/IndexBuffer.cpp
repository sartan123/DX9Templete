#include "IndexBuffer.h"



IndexBuffer::IndexBuffer(LPDIRECT3DDEVICE9 p)
: Graphic(p)
{
	InitializeResource();
}


IndexBuffer::~IndexBuffer()
{
}

bool IndexBuffer::InitializeResource()
{
	const SimpleVertex vertices[4] =
	{
		{ 10.0f, 10.0f, 0.0f, 1.0f, 0xffff7f7f },
		{ 50.0f, 10.0f, 0.0f, 1.0f, 0xff7fff7f },
		{ 10.0f, 50.0f, 0.0f, 1.0f, 0xff7f7fff },
		{ 50.0f, 50.0f, 0.0f, 1.0f, 0xffffffff },
	};
	// 頂点バッファの生成
	g_pVertexBuffer = CreateVertexBuffer(vertices, sizeof(vertices));
	if (g_pVertexBuffer == NULL) {
		return false;
	}
	return true;
}

IDirect3DIndexBuffer9* IndexBuffer::CreateIndexBuffer(const UINT16* pIndeces, size_t size)
{
	IDirect3DIndexBuffer9* pIndexBuffer;
	if (FAILED(pDevice->CreateIndexBuffer(size, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIndexBuffer, NULL)))
	{
		return NULL;
	}
	void* pData;
	if (SUCCEEDED(pIndexBuffer->Lock(0, size, &pData, 0)))
	{
		memcpy(pData, pIndeces, size);
		pIndexBuffer->Unlock();
	}
	return pIndexBuffer;
}

IDirect3DVertexBuffer9* IndexBuffer::CreateVertexBuffer(const void* pVertices, size_t size)
{
	IDirect3DVertexBuffer9* pVertexBuffer;
	if (FAILED(pDevice->CreateVertexBuffer(size, 0, 0, D3DPOOL_MANAGED, &pVertexBuffer, NULL)))
	{
		return NULL;
	}
	void* pData;
	if (SUCCEEDED(pVertexBuffer->Lock(0, size, &pData, 0)))
	{
		memcpy(pData, pVertices, size);
		pVertexBuffer->Unlock();
	}
	return pVertexBuffer;
}

void IndexBuffer::Draw()
{
	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(g_pVertexBuffer));
	// 描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}