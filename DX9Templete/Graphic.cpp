#include "Graphic.h"

Graphic::Graphic(LPDIRECT3DDEVICE9 p, DWORD fvf, D3DPRIMITIVETYPE type, UINT primitive)
: pDevice(p)
, FVF(fvf)
, Type(type)
, PrimitiveCount(primitive)
{
	vertices[0] = { 10.0f, 10.0f, 0.0f, 1.0f, 0xffffffff };
	vertices[1] = { 50.0f, 10.0f, 0.0f, 1.0f, 0xffffffff };
	vertices[2] = { 10.0f, 50.0f, 0.0f, 1.0f, 0xffffffff };
	vertices[3] = { 50.0f, 50.0f, 0.0f, 1.0f, 0xffffffff };
}


Graphic::~Graphic()
{
}

void Graphic::Draw()
{
	pDevice->SetFVF(FVF);
	pDevice->DrawPrimitiveUP(Type, PrimitiveCount, vertices, sizeof(SimpleVertex));
}
