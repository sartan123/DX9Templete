#pragma once
#include "stddef.h"
#include <d3d9.h>
#include <d3dx9.h>

class TextFont
{
private:
	ID3DXFont* pFont;
	D3DXFONT_DESC desc;
	RECT mRect;
	D3DCOLOR mColor;
	std::string str;
public:
	TextFont(const char* message);
	~TextFont();
	HRESULT Initialize(IDirect3DDevice9* device);
	void Draw();
	void ChangeText(const char* message){ str = message; }
};

