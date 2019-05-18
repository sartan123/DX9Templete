#pragma once
#include "stddef.h"

class Graphic
{
protected:
	LPDIRECT3DDEVICE9 pDevice;
	DWORD FVF;
	D3DPRIMITIVETYPE Type;
	UINT PrimitiveCount;
public:
	Graphic(){}
	Graphic(LPDIRECT3DDEVICE9 p, DWORD fvf = D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPRIMITIVETYPE type = D3DPT_TRIANGLESTRIP, UINT primitive = 2);
	~Graphic();
	virtual void Draw() = 0;
};
