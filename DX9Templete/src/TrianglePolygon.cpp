#include "TrianglePolygon.h"



TrianglePolygon::TrianglePolygon()
{
}


TrianglePolygon::~TrianglePolygon()
{
}

void TrianglePolygon::LoadShader(IDirect3DDevice9* device)
{
	HRESULT hr;
	std::wstring path = GetExecutionDirectory();
	path += std::wstring(L"\\");
	path += L"SampleVertexShader.cso";
	std::ifstream infile(path, std::ifstream::binary);
	if (!infile)
	{
		throw _T("error");
	}
	std::vector<uint8_t> buf;
	int size = static_cast<int>(infile.seekg(0, std::ifstream::end).tellg());
	buf.resize(size);
	infile.seekg(0, std::ifstream::beg);
	infile.read(reinterpret_cast<char*>(buf.data()), size);
	hr = device->CreateVertexShader(reinterpret_cast<DWORD*>(buf.data()), &pVertexShader);
	if (FAILED(hr)) {
		throw _T("error");
	}
}

void TrianglePolygon::Draw(IDirect3DDevice9* device)
{
	device->SetVertexShader(pVertexShader);
	device->SetVertexDeclaration(pVertexDeclaration);
	device->SetStreamSource(0, pVertexBuffer, 0, sizeof(Vertex));
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}

void TrianglePolygon::SetVertexBuffer(IDirect3DDevice9* device)
{
	const Vertex vertices[] = {
		{DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), DirectX::PackedVector::XMCOLOR(0xff00ff00)},
		{DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f), DirectX::PackedVector::XMCOLOR(0xffff0000)},
		{DirectX::XMFLOAT3(-1.0f,0.0f, 0.0f), DirectX::PackedVector::XMCOLOR(0xff0000ff)},
	};

	HRESULT hr;
	hr = device->CreateVertexBuffer(sizeof(vertices), 0, 0, D3DPOOL_DEFAULT, &pVertexBuffer, nullptr);
	if (FAILED(hr)) {
		throw _T("error");
	}
	void* p = nullptr;
	hr = pVertexBuffer->Lock(0, 0, &p, 0);
	if (SUCCEEDED(hr))
	{
		memcpy_s(p, sizeof(vertices), vertices, sizeof(vertices));
		pVertexBuffer->Unlock();
	}
}

void TrianglePolygon::SetVertexDeclaration(IDirect3DDevice9* device)
{
	HRESULT hr;
	D3DVERTEXELEMENT9 decl[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
		D3DDECL_END()
	};
	hr = device->CreateVertexDeclaration(decl, &pVertexDeclaration);
	if (FAILED(hr)) {
		throw _T("error");
	}
}