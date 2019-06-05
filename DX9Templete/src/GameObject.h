#pragma once
#include "stddef.h"
#include <d3d9.h>
#include <d3dx9.h>

class GameObject
{
private:
	IDirect3DDevice9* device;
public:
	GameObject(IDirect3DDevice9* pDevice);
	~GameObject();
	virtual HRESULT Initialize() = 0;
	virtual void Draw() = 0;
protected:
	IDirect3DDevice9* GetDevice() { return device; }
};

