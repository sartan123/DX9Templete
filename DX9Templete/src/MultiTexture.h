#pragma once
#include "BasicTexture.h"
class MultiTexture : public BasicTexture
{
protected:
	LPDIRECT3DTEXTURE9 mTexture2;
	D3DXHANDLE mTextureHandler2;
public:
	MultiTexture();
	~MultiTexture();
	virtual HRESULT Create(LPDIRECT3DDEVICE9 device);
	virtual HRESULT SetPrimitiveInfo(IDirect3DDevice9* device);
	virtual void Draw(IDirect3DDevice9* device);
	virtual HRESULT SetShader(IDirect3DDevice9* device);
};

