#include "TextFont.h"

TextFont::TextFont(const char* message)
: str(message)
,mColor(0xffffffff)
{
}

TextFont::~TextFont()
{
}

HRESULT TextFont::Initialize(IDirect3DDevice9* device)
{
	ZeroMemory(&desc, sizeof(desc));
	desc.Height = 60;
	desc.Width = desc.Height / 2;
	desc.Weight = 400;
	desc.MipLevels = D3DX_DEFAULT;
	desc.Italic = FALSE;
	desc.CharSet = SHIFTJIS_CHARSET;
	desc.OutputPrecision = OUT_DEFAULT_PRECIS;
	desc.Quality = DEFAULT_QUALITY;
	desc.PitchAndFamily = FIXED_PITCH | FF_MODERN;
	ZeroMemory(desc.FaceName, sizeof(desc.FaceName));

	D3DXCreateFontIndirect(device, &desc, &pFont);

	return S_OK;
}

void TextFont::Draw()
{
	SetRect(&mRect, 0, 0, 0, 0);
	pFont->DrawText(NULL, str.c_str(), -1, &mRect, DT_LEFT | DT_CALCRECT, mColor);
	OffsetRect(&mRect, 0, 0);
	pFont->DrawText(NULL, str.c_str(), -1, &mRect, DT_LEFT, mColor);
}
