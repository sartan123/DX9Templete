#pragma once
#include "stddef.h"
#include "TrianglePolygon.h"
#include <d3d9.h>
#include <d3dx9.h>

class Square: public TrianglePolygon
{
public:
	Square();
	~Square();
	virtual void Draw(LPDIRECT3DDEVICE9 device);
	virtual HRESULT SetPrimitiveInfo(IDirect3DDevice9* device);
};

