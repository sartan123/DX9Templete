#include "Graphic.h"

Graphic::Graphic(LPDIRECT3DDEVICE9 p, DWORD fvf, D3DPRIMITIVETYPE type, UINT primitive)
: pDevice(p)
, FVF(fvf)
, Type(type)
, PrimitiveCount(primitive)
{
}


Graphic::~Graphic()
{
}
