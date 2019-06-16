#include "Square.h"

Square::Square()
: TrianglePolygon()
{
}


Square::~Square()
{
	Destroy();
}

void Square::Draw(LPDIRECT3DDEVICE9 device)
{
	if (device == 0)
	{
		return;
	}
	if (mVertexBuffer == 0)
	{
		return;
	}

	device->SetVertexDeclaration(mVertexDec);
	device->SetStreamSource(0, mVertexBuffer, 0, sizeof(VERTEX_POS));
	device->SetStreamSource(1, mVertexColorBuffer, 0, sizeof(VERTEX_COLOR));

	mEffect->SetTechnique(mTechHandle);
	mEffect->SetMatrix(mWorldHandle, &(m_world));
	mEffect->SetMatrix(mViewingHandle, &(m_view));
	mEffect->SetMatrix(mProjectionHandle, &(m_projection));
	mEffect->CommitChanges();

	mEffect->Begin(0, 0);
	mEffect->BeginPass(0);

	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	mEffect->EndPass();
	mEffect->End();
}

HRESULT Square::SetPrimitiveInfo(IDirect3DDevice9* device)
{
	mPrimitiveCount = 4;

	if (FAILED(device->CreateVertexBuffer(mPrimitiveCount * sizeof(VERTEX_POS), D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &mVertexBuffer, NULL)))
	{
		return E_FAIL;
	}

	mVertexBuffer->Lock(0, 0, (void**)&mVertexPos, 0);
	mVertexPos[0].p = D3DXVECTOR3(-1.5f, 1.5f, 0.0f);
	mVertexPos[1].p = D3DXVECTOR3(1.5f, 1.5f, 0.0f);
	mVertexPos[2].p = D3DXVECTOR3(-1.5f, -1.5f, 0.0f);
	mVertexPos[3].p = D3DXVECTOR3(1.5f, -1.5f, 0.0f);
	mVertexBuffer->Unlock();

	if (FAILED(device->CreateVertexBuffer(mPrimitiveCount * sizeof(VERTEX_COLOR), D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &mVertexColorBuffer, NULL)))
	{
		return E_FAIL;
	}
	mVertexColorBuffer->Lock(0, 0, (void**)&mVertexColor, 0);
	mVertexColor[0].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	mVertexColor[1].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	mVertexColor[2].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	mVertexColor[3].color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	mVertexColorBuffer->Unlock();

	return S_OK;
}