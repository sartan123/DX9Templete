#include "Sprite.h"



Sprite::Sprite()
:pTexture(nullptr)
{
	pos.x = 0.0f;
	pos.y = 0.0f;
}


Sprite::~Sprite()
{
	SafeRelease(pTexture);
}

void Sprite::Draw(IDirect3DDevice9* pDevice)
{
	D3DSURFACE_DESC desc;
	pTexture->GetLevelDesc(0, &desc);

	Vertex vtx[4] = {
		{ pos.x + desc.Width, pos.y, 0.0f, 1.0f, 1.0f, 0.0f},
		{ pos.x + desc.Width, pos.y + desc.Height, 0.0f, 1.0f, 1.0f, 1.0f},
		{ pos.x, pos.y, 0.0f, 1.0f, 0.0f, 0.0f},
		{ pos.x, pos.y + desc.Height, 0.0f, 1.0f, 0.0f, 1.0f}
	};

	pDevice->SetTexture(0, pTexture);
	pDevice->SetFVF(SPRITE_FVF);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vtx, sizeof(Vertex));
}

HRESULT Sprite::LoadTexture(IDirect3DDevice9* pDevice, const char* file_name)
{
	if (FAILED(D3DXCreateTextureFromFile(pDevice, file_name, &pTexture)))
	{
		return E_FAIL;
	}
	return S_OK;
}