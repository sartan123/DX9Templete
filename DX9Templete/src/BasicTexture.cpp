#include "BasicTexture.h"

BasicTexture::BasicTexture(IDirect3DDevice9* pDevice)
: GameObject(pDevice)
{
}


BasicTexture::~BasicTexture()
{
}

HRESULT BasicTexture::Initialize()
{
	D3DVERTEXELEMENT9 vertex[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 1, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};

	const VERTEX_TEX vertices[] = {
		D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(1.0f, 1.0f),
	};

	if (FAILED(GetDevice()->CreateVertexBuffer(sizeof(vertices), 0, 0, D3DPOOL_DEFAULT, &mVertexBuffer, nullptr)))
	{
		return E_FAIL;
	}
	VERTEX_TEX* v;
	mVertexBuffer->Lock(0, 0, (void**)&v, 0);
	memcpy_s(v, sizeof(vertices), vertices, sizeof(vertices));
	mVertexBuffer->Unlock();

}