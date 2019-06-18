#pragma once
#include "GameObject.h"
class Particle : public GameObject
{
public:
	Particle();
	~Particle();
	virtual void Draw(LPDIRECT3DDEVICE9 device);
	virtual HRESULT Create(LPDIRECT3DDEVICE9 device);
	virtual HRESULT SetShader(IDirect3DDevice9* device);
	virtual void SetViewMatrix();
protected:
	struct VERTEX_POS
	{
		D3DXVECTOR3 pos;
		FLOAT p_size;
		D3DXVECTOR3 direction;
		FLOAT life_time;
		FLOAT start_time;
	};
	static const int NUM_SPRITE = 1024;
	DWORD m_beginTime;

	LPDIRECT3DVERTEXBUFFER9	mVertexBuffer;
	LPDIRECT3DVERTEXDECLARATION9 mVertexDec;;
	LPDIRECT3DTEXTURE9		mTexture;

	LPD3DXEFFECT	mEffect;
	D3DXHANDLE	mTechHandle;

	D3DXHANDLE	mWorldHandle;
	D3DXHANDLE	mViewingHandle;
	D3DXHANDLE	mProjectionHandle;
	D3DXHANDLE	mTimeHandle;
	D3DXHANDLE	mTextureHandle;
};

