#pragma once
#include "stddef.h"
#include <d3d9.h>
#include <d3dx9.h>

class MaterialMesh
{
private:
	D3DMATERIAL9 material;
	ID3DXMesh *pMesh;
public:
	MaterialMesh();
	~MaterialMesh();
	HRESULT Initialize(IDirect3DDevice9* pDevice);
	void Draw(IDirect3DDevice9* pDevice);
};

