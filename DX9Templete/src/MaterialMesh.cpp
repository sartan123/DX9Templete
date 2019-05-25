#include "MaterialMesh.h"

#pragma comment(lib, "winmm.lib")


MaterialMesh::MaterialMesh()
{
}


MaterialMesh::~MaterialMesh()
{
}

HRESULT MaterialMesh::Initialize(IDirect3DDevice9* pDevice)
{
	HRESULT hr = D3DXCreateBox(pDevice, 0.5, 0.5f, 0.5f, &pMesh, NULL);
	if (FAILED(hr))
	{
		return E_FAIL;
	}
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Diffuse.r = material.Ambient.r = 0.0;
	material.Diffuse.g = material.Ambient.g = 0.0;
	material.Diffuse.b = material.Ambient.b = 1.0;
	material.Diffuse.a = material.Ambient.a = 1.0;
	pDevice->SetMaterial(&material);

	pDevice->SetRenderState(D3DRS_DITHERENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x000f0f0f);
	return S_OK;
}

void MaterialMesh::Draw(IDirect3DDevice9* pDevice)
{
	pMesh->DrawSubset(0);
}