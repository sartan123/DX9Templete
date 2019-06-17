#include "MultiTexture.h"



MultiTexture::MultiTexture()
:BasicTexture()
{
}


MultiTexture::~MultiTexture()
{
}

HRESULT MultiTexture::Create(LPDIRECT3DDEVICE9 device)
{
	D3DVERTEXELEMENT9 vertex_elements[] =
	{
		{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{1, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		{2, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1},
		D3DDECL_END()
	};

	device->CreateVertexDeclaration(vertex_elements, &mVertexDec);

	SetWorldMatrix();

	SetPrimitiveInfo(device);

	if (FAILED(SetProjectionMatrix(device)))
	{
		return E_FAIL;
	}

	SetViewMatrix();

	if (FAILED(SetShader(device)))
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT MultiTexture::SetShader(IDirect3DDevice9* device)
{
	HRESULT hr;
	LPD3DXBUFFER errors = 0;
	std::string file_path = std::string("..\\DX9Templete\\resource\\Shader\\multi_texture_shader.fx");
	hr = D3DXCreateEffectFromFile(device, file_path.c_str(), 0, 0, D3DXSHADER_DEBUG, 0, &mEffect, &errors);
	if (hr)
	{
		return E_FAIL;
	}
	if (errors)
	{
		return E_FAIL;
	}

	mTechHandle = mEffect->GetTechniqueByName("BasicTech");
	mWorldHandle = mEffect->GetParameterByName(0, "g_world");
	mViewingHandle = mEffect->GetParameterByName(0, "g_viewing");
	mProjectionHandle = mEffect->GetParameterByName(0, "g_projection");
	mColorHandle = mEffect->GetParameterByName(0, "g_color");
	mTextureHandler = mEffect->GetParameterByName(0, "g_texture0");
	mTextureHandler2 = mEffect->GetParameterByName(0, "g_texture1");

	return S_OK;
}

HRESULT MultiTexture::SetPrimitiveInfo(IDirect3DDevice9* device)
{
	mPrimitiveCount = 4;

	if (FAILED(device->CreateVertexBuffer(mPrimitiveCount * sizeof(VERTEX_POS), D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &mVertexBuffer, NULL)))
	{
		return E_FAIL;
	}

	mVertexBuffer->Lock(0, 0, (void**)&mVertexPos, 0);
	mVertexPos[0].p = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	mVertexPos[1].p = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	mVertexPos[2].p = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	mVertexPos[3].p = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	mVertexBuffer->Unlock();

	if (FAILED(device->CreateVertexBuffer(mPrimitiveCount * sizeof(VERTEX_TEX), D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &mVertexTextureBuffer, NULL)))
	{
		return E_FAIL;
	}
	VERTEX_TEX* texture;
	mVertexTextureBuffer->Lock(0, 0, (void**)&texture, 0);
	texture[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	texture[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	texture[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	texture[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	mVertexTextureBuffer->Unlock();

	if (FAILED(D3DXCreateTextureFromFile(device, "..\\DX9Templete\\resource\\Image\\tex0.bmp", &mTexture)))
	{
		return E_FAIL;
	}
	if (FAILED(D3DXCreateTextureFromFile(device, "..\\DX9Templete\\resource\\Image\\tex1.bmp", &mTexture2)))
	{
		return E_FAIL;
	}

	return S_OK;
}

void MultiTexture::Draw(IDirect3DDevice9* device)
{
	if (device == 0)
	{
		return;
	}
	if (mVertexBuffer == 0)
	{
		return;
	}

	mRotate += 1.5;
	D3DXMatrixRotationY(&m_rotate, D3DXToRadian(mRotate));

	m_world = m_scale * m_rotate * m_transelate;

	D3DXVECTOR4 tmpColor;
	tmpColor.x = 0.0f;
	tmpColor.y = 0.0f;
	tmpColor.z = 0.0f;
	tmpColor.w = 1.0f;


	device->SetVertexDeclaration(mVertexDec);
	device->SetStreamSource(0, mVertexBuffer, 0, sizeof(VERTEX_POS));
	device->SetStreamSource(1, mVertexTextureBuffer, 0, sizeof(VERTEX_TEX));

	mEffect->SetTechnique(mTechHandle);
	mEffect->SetMatrix(mWorldHandle, &(m_world));
	mEffect->SetMatrix(mViewingHandle, &(m_view));
	mEffect->SetMatrix(mProjectionHandle, &(m_projection));
	mEffect->SetVector(mColorHandle, &tmpColor);
	mEffect->SetTexture(mTextureHandler, mTexture);
	mEffect->SetTexture(mTextureHandler2, mTexture2);
	mEffect->CommitChanges();

	mEffect->Begin(0, 0);
	mEffect->BeginPass(0);

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	mEffect->EndPass();
	mEffect->End();
}
