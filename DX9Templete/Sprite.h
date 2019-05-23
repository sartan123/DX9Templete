#pragma once
#include "stddef.h"
#include <d3d9.h>
#include <d3dx9.h>

class Sprite
{
private:
	struct Vertex {
		float x, y, z;// 3�������W
		float rhw;	// 2D�ϊ��ς݃t���O
		float u, v;	// UV���W
	};
	static const DWORD SPRITE_FVF = D3DFVF_XYZRHW | D3DFVF_TEX1;
	D3DXVECTOR2 pos;

	int width;
	int height;
	LPDIRECT3DTEXTURE9 pTexture;

public:
	Sprite();
	~Sprite();
	void SetPosition(float x, float y) { pos.x = x; pos.y = y; }
	void SetWidth(int Width, int Height){ width = Width; height = Height; }

	void Draw(IDirect3DDevice9* pDevice);
	HRESULT LoadTexture(IDirect3DDevice9* pDevice, const char* file_name);
};

