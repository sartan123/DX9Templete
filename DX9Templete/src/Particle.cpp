#include "Particle.h"



Particle::Particle()
	: GameObject()
{
}


Particle::~Particle()
{
}

HRESULT Particle::Create(LPDIRECT3DDEVICE9 device)
{
	D3DVERTEXELEMENT9 m_vertex_elements[] =
	{
		{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_PSIZE, 0},
		{0, 16, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		{0, 28, D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1},
		{0, 32, D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2},
		D3DDECL_END()
	};
	device->CreateVertexDeclaration(m_vertex_elements, &mVertexDec);

	if (FAILED(device->CreateVertexBuffer(NUM_SPRITE * sizeof(VERTEX_POS), D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &mVertexBuffer, NULL)))
	{
		return E_FAIL;
	}

	timeBeginPeriod(1);
	m_beginTime = timeGetTime();

	SetWorldMatrix();

	SetViewMatrix();

	if (FAILED(SetProjectionMatrix(device)))
	{
		return E_FAIL;
	}

	VERTEX_POS* v;
	mVertexBuffer->Lock(0, 0, (void**)&v, 0);

	for (int i = 0; i < NUM_SPRITE; i++)
	{
		v[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		v[i].p_size = ((float)rand() / (float)RAND_MAX) * 30.0f + 15.0f;
		v[i].direction.x = ((float)rand() / (float)RAND_MAX) * 30.0f - 15.0f;
		v[i].direction.y = ((float)rand() / (float)RAND_MAX) * 30.0f + 30.0f;
		v[i].direction.z = ((float)rand() / (float)RAND_MAX) * 30.0f - 15.0f;

		v[i].life_time = ((float)rand() / (float)RAND_MAX) * 2.0f + 2.0f;
		v[i].start_time = ((float)rand() / (float)RAND_MAX) * 4.0f;
	}

	mVertexBuffer->Unlock();

	if (FAILED(SetShader(device)))
	{
		return E_FAIL;
	}

	return S_OK;
}

void Particle::SetViewMatrix()
{
	D3DXMatrixIdentity(&m_view);
	D3DXMatrixLookAtLH(&m_view,
		&D3DXVECTOR3(0.0f, 50.0f, -100.0f),
		&D3DXVECTOR3(0.0f, 50.0f, 0.0f),
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));
}

HRESULT Particle::SetShader(IDirect3DDevice9* device)
{
	HRESULT hr;
	LPD3DXBUFFER errors = 0;
	std::string file_path = std::string("..\\DX9Templete\\resource\\Shader\\psprite_shader .fx");
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
	mTimeHandle = mEffect->GetParameterByName(0, "g_time");
	mTextureHandle = mEffect->GetParameterByName(0, "g_texture");
	
	D3DXCreateTextureFromFile(device, TEXT("..\\DX9Templete\\resource\\Image\\fire.bmp"), &mTexture);

	return S_OK;
}

void Particle::Draw(LPDIRECT3DDEVICE9 device)
{
	if (device == 0)
	{
		return;
	}
	if (mVertexBuffer == 0)
	{
		return;
	}

	m_world = m_scale * m_rotate * m_transelate;

	device->SetVertexDeclaration(mVertexDec);
	device->SetStreamSource(0, mVertexBuffer, 0, sizeof(VERTEX_POS));

	mEffect->SetTechnique(mTechHandle);
	mEffect->SetMatrix(mWorldHandle, &(m_world));
	mEffect->SetMatrix(mViewingHandle, &(m_view));
	mEffect->SetMatrix(mProjectionHandle, &(m_projection));
	mEffect->SetTexture(mTextureHandle, mTexture);

	DWORD tmpCurTime = timeGetTime();
	tmpCurTime = tmpCurTime - m_beginTime;
	float tmpTime = (float)tmpCurTime / 1000.0f;
	mEffect->SetFloat(mTimeHandle, tmpTime);

	mEffect->CommitChanges();

	mEffect->Begin(0, 0);
	mEffect->BeginPass(0);

	//device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	device->DrawPrimitive(D3DPT_POINTLIST, 0, NUM_SPRITE);

	mEffect->EndPass();
	mEffect->End();
}