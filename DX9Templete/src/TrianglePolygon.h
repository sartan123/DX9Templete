#pragma once
#include "stddef.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

class TrianglePolygon
{
private:
	IDirect3DVertexBuffer9* pVertexBuffer;
	IDirect3DVertexShader9*	pVertexShader;
	IDirect3DVertexDeclaration9* pVertexDeclaration;

	struct Vertex {
		DirectX::XMFLOAT3 Pos;
		DirectX::PackedVector::XMCOLOR Color;
	};
public:
	TrianglePolygon();
	~TrianglePolygon();
	void LoadShader(IDirect3DDevice9* device);
	void SetVertexBuffer(IDirect3DDevice9* device);
	void SetVertexDeclaration(IDirect3DDevice9* device);
	void Draw(IDirect3DDevice9* device);
};

