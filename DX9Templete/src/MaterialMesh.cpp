#include "MaterialMesh.h"

#pragma comment(lib, "winmm.lib")


MaterialMesh::MaterialMesh()
{
}


MaterialMesh::~MaterialMesh()
{
}

HRESULT MaterialMesh::Create(LPDIRECT3DDEVICE9 device)
{
	if (device == 0) {
		return E_FAIL;
	}

	if (FAILED(LoadMeshFile(device)))
	{
		return E_FAIL;
	}

	// ビューポートの取得
	D3DVIEWPORT9    vp;
	if (FAILED(device->GetViewport(&vp))) {
		return E_FAIL;
	}

	// アスペクト比の計算
	float aspect;
	aspect = (float)vp.Width / (float)vp.Height;

	// プロジェクション行列の初期化
	D3DXMatrixIdentity(&m_projection);
	D3DXMatrixPerspectiveFovLH(&m_projection, D3DXToRadian(45.0f), aspect, 1.0f, 1000.0f);

	// ビューイング行列の初期化
	D3DXMatrixIdentity(&m_view);
	D3DXMatrixLookAtLH(&m_view,
		&D3DXVECTOR3(5.0, 5.0f, -5.0f),
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	D3DXMatrixIdentity(&m_world);

	// シェーダプログラムの読み込みとコンパイル
	LPD3DXBUFFER	errors = 0;
	D3DXCreateEffectFromFile(device, TEXT("..\\DX9Templete\\resource\\Shader\\light_diffuse.fx"), 0, 0, D3DXSHADER_DEBUG, 0, &m_pFX, &errors);
	if (errors) {
		return E_FAIL;
	}

	// シェーダプログラムへテクニックへのハンドルの取得
	m_hTech = m_pFX->GetTechniqueByName("BasicTech");

	// シェーダープログラムのグローバル変数のハンドルの取得
	m_hWorld = m_pFX->GetParameterByName(0, "g_world");
	m_hWorldInv = m_pFX->GetParameterByName(0, "g_world_inv");
	m_hView = m_pFX->GetParameterByName(0, "g_view");
	m_hProj = m_pFX->GetParameterByName(0, "g_proj");
	m_hColor0 = m_pFX->GetParameterByName(0, "g_color0");
	m_hColor1 = m_pFX->GetParameterByName(0, "g_color1");
	m_hLightDir = m_pFX->GetParameterByName(0, "g_light_dir");
	m_hTexture = m_pFX->GetParameterByName(0, "g_texture");

	return S_OK;
}

void MaterialMesh::Draw(IDirect3DDevice9* device)
{
	if (device == 0) {
		return;
	}

	// テクニックの設定（シェーダプログラムの設定）
	m_pFX->SetTechnique(m_hTech);

	// シェーダーのグローバル変数の値の設定
	m_pFX->SetMatrix(m_hWorld, &m_world);
	D3DXMatrixInverse(&m_world_inv, NULL, &m_world);
	m_pFX->SetMatrix(m_hWorldInv, &m_world_inv);
	m_pFX->SetMatrix(m_hView, &m_view);
	m_pFX->SetMatrix(m_hProj, &m_projection);

	// ライトのベクトルの計算
	D3DXVECTOR4		tmpLightDirection;
	tmpLightDirection.x = 0.5f;
	tmpLightDirection.y = 1.0f;
	tmpLightDirection.z = -2.0f;
	tmpLightDirection.w = 0.0f;
	D3DXVec4Normalize(&tmpLightDirection, &tmpLightDirection);
	m_pFX->SetVector(m_hLightDir, &tmpLightDirection);

	// シェーダプログラムの開始宣言
	m_pFX->Begin(0, 0);

	// Xファイルのの描画処理
	D3DXVECTOR4		tmpColor;

	// マテリアル情報を取り出す
	D3DXMATERIAL*	mD3DXMaterials = (D3DXMATERIAL*)m_pD3DXMtrlBuffer->GetBufferPointer();
	for (DWORD i = 0; i < m_numMtrl; i++) {

		if (m_pTextures[i] != 0) {
			m_pFX->BeginPass(0);
		}
		else {
			m_pFX->BeginPass(1);
		}

		m_pFX->SetTexture(m_hTexture, m_pTextures[i]);

		// マテリアルのコピー
		tmpColor.x = mD3DXMaterials[i].MatD3D.Emissive.r;
		tmpColor.y = mD3DXMaterials[i].MatD3D.Emissive.g;
		tmpColor.z = mD3DXMaterials[i].MatD3D.Emissive.b;
		m_pFX->SetVector(m_hColor0, &tmpColor);
		tmpColor.x = mD3DXMaterials[i].MatD3D.Diffuse.r;
		tmpColor.y = mD3DXMaterials[i].MatD3D.Diffuse.g;
		tmpColor.z = mD3DXMaterials[i].MatD3D.Diffuse.b;
		tmpColor.w = 1.0f;
		m_pFX->SetVector(m_hColor1, &tmpColor);
		m_pFX->CommitChanges();

		// 分割されたメッシュの描画
		m_pMesh->DrawSubset(i);

		m_pFX->EndPass();
	}

	// シェーダプログラムの終了宣言
	m_pFX->End();
}

HRESULT MaterialMesh::LoadMeshFile(LPDIRECT3DDEVICE9 device)
{
	// Ｘファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(TEXT("..\\DX9Templete\\resource\\Mesh\\cube-tex01.X"),// Ｘファイルのファイル名
		D3DXMESH_SYSTEMMEM,	// メッシュをシステムメモリに展開する
		device,			// D3Dデバイスオブジェクト
		NULL,
		&m_pD3DXMtrlBuffer,	// 属性バッファの設定
		NULL,
		&m_numMtrl,			// 属性の数
		&m_pMesh))) {		// 格納先のメッシュ
		return E_FAIL;
	}

	// Xファイルで指定されているテクスチャファイルの読み込み
	m_pTextures = new LPDIRECT3DTEXTURE9[m_numMtrl];
	D3DXMATERIAL*	mD3DXMaterials = (D3DXMATERIAL*)m_pD3DXMtrlBuffer->GetBufferPointer();
	wchar_t tmp_texture[256];
	for (DWORD i = 0; i < m_numMtrl; i++) {
		if (mD3DXMaterials[i].pTextureFilename != 0) {
			MultiByteToWideChar(CP_ACP, 0,
				mD3DXMaterials[i].pTextureFilename,
				-1,
				tmp_texture,
				sizeof(tmp_texture));
			char temp[256];
			size_t num;
			size_t length = 256;
			wcstombs_s(&num, temp, length, tmp_texture, length);
			D3DXCreateTextureFromFile(device, temp, &m_pTextures[i]);
		}
		else {
			m_pTextures[i] = 0;
		}
	}
	return S_OK;
}