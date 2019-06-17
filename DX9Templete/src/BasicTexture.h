#pragma once
#include "stddef.h"
#include "TrianglePolygon.h"
#include <d3d9.h>
#include <d3dx9.h>


class BasicTexture : public TrianglePolygon
{
protected:
	LPDIRECT3DTEXTURE9 mTexture;
	LPDIRECT3DVERTEXBUFFER9 mVertexTextureBuffer;
	D3DXHANDLE              mWvpHander;
	D3DXHANDLE				mTextureHandler;
	struct VERTEX_TEX {
		D3DXVECTOR2 tex;
	};
public:
	BasicTexture();
	~BasicTexture();
	virtual HRESULT Create(LPDIRECT3DDEVICE9 device);
	virtual void Draw(IDirect3DDevice9* device);
	virtual HRESULT SetShader(IDirect3DDevice9* device);
	virtual HRESULT SetPrimitiveInfo(IDirect3DDevice9* device);
};

