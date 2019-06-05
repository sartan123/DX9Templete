#pragma once
#include "stddef.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

struct Vertex {
	DirectX::XMFLOAT3 Pos;
	DirectX::PackedVector::XMCOLOR Color;
};
//struct Vertex {
//	DirectX::XMFLOAT3 Pos;
//};

class Square
{
public:
	Square();
	~Square();
	HRESULT Initialize(IDirect3DDevice9* pDevice);
	void Draw(IDirect3DDevice9* pDevice);
	void SetVertexShader(IDirect3DDevice9* pDevice);
	void SetPixelShader(IDirect3DDevice9* pDevice);
private:
	LPDIRECT3DVERTEXDECLARATION9 mVertexDec;
	LPDIRECT3DVERTEXBUFFER9 mVertexBuffer;
	IDirect3DVertexShader9*	pVertexShader;
	IDirect3DPixelShader9* pPixelShader;
};

