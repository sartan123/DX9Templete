#include "Square.h"

Square::Square()
:mVertexDec(nullptr)
,mVertexBuffer(nullptr)
{
}


Square::~Square()
{
}

HRESULT Square::Initialize(IDirect3DDevice9* pDevice)
{
	const Vertex vertices[] = {
		{DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), DirectX::PackedVector::XMCOLOR(0xff00ff00)},
		{DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), DirectX::PackedVector::XMCOLOR(0x0000ffff)},
		{DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f), DirectX::PackedVector::XMCOLOR(0xffff0000)},
		{DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f), DirectX::PackedVector::XMCOLOR(0xff0000ff)},
	};
	//const Vertex vertices[] = {
	//	DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
	//	DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f),
	//	DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f), 
	//	DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f),
	//};

	D3DVERTEXELEMENT9 vertex[] = 
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
		D3DDECL_END()
	};

	pDevice->CreateVertexDeclaration(vertex, &mVertexDec);
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(vertices), 0, 0, D3DPOOL_DEFAULT, &mVertexBuffer, nullptr)))
	{
		return E_FAIL;
	}
	Vertex* v;
	mVertexBuffer->Lock(0, 0, (void**)&v, 0);
	memcpy_s(v, sizeof(vertices), vertices, sizeof(vertices));
	mVertexBuffer->Unlock();

	SetVertexShader(pDevice);
	SetPixelShader(pDevice);

	return S_OK;
}

void Square::Draw(IDirect3DDevice9* pDevice)
{
	pDevice->SetVertexShader(pVertexShader);
	pDevice->SetPixelShader(pPixelShader);
	pDevice->SetVertexDeclaration(mVertexDec);
	pDevice->SetStreamSource(0, mVertexBuffer, 0, sizeof(Vertex));
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void Square::SetVertexShader(IDirect3DDevice9* pDevice)
{
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

	pDevice->CreateVertexShader(reinterpret_cast<DWORD*>(buf.data()), &pVertexShader);
}

void Square::SetPixelShader(IDirect3DDevice9* pDevice)
{
	std::wstring path = GetExecutionDirectory();
	path += std::wstring(L"\\");
	path += L"SquarePixelShader.cso";
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

	pDevice->CreatePixelShader(reinterpret_cast<DWORD*>(buf.data()), &pPixelShader);
}