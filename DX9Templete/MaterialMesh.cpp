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
	if (FAILED(D3DXCreateTeapot(pDevice, &pMesh, NULL)))
	{
		return E_FAIL;
	}
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Diffuse.r = material.Ambient.r = 0.0;
	material.Diffuse.g = material.Ambient.g = 1.0;
	material.Diffuse.b = material.Ambient.b = 1.0;
	material.Diffuse.a = material.Ambient.a = 1.0;
	pDevice->SetMaterial(&material);

	D3DXVECTOR3 vecLightDirUnnormalized(-1.0f, -1.0f, 2.0f);
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;

	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecLightDirUnnormalized);
	light.Position.x = -1.0f;
	light.Position.y = -1.0f;
	light.Position.z = 2.0f;
	light.Range = 1000.0f;
	pDevice->SetLight(0, &light);
	pDevice->LightEnable(0, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

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