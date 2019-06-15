#pragma once
#include "stddef.h"
#include "GameObject.h"
#include <d3d9.h>
#include <d3dx9.h>

struct VERTEX_TEX {
	D3DXVECTOR2 tex;
};

class BasicTexture : public GameObject
{
private:
	LPDIRECT3DVERTEXBUFFER9 mVertexBuffer;
	LPDIRECT3DTEXTURE9 mTexture;
public:
	BasicTexture(IDirect3DDevice9* pDevice);
	~BasicTexture();

	HRESULT Initialize();
};

