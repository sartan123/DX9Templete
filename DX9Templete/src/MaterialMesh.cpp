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

	// �r���[�|�[�g�̎擾
	D3DVIEWPORT9    vp;
	if (FAILED(device->GetViewport(&vp))) {
		return E_FAIL;
	}

	// �A�X�y�N�g��̌v�Z
	float aspect;
	aspect = (float)vp.Width / (float)vp.Height;

	// �v���W�F�N�V�����s��̏�����
	D3DXMatrixIdentity(&m_projection);
	D3DXMatrixPerspectiveFovLH(&m_projection, D3DXToRadian(45.0f), aspect, 1.0f, 1000.0f);

	// �r���[�C���O�s��̏�����
	D3DXMatrixIdentity(&m_view);
	D3DXMatrixLookAtLH(&m_view,
		&D3DXVECTOR3(5.0, 5.0f, -5.0f),
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	D3DXMatrixIdentity(&m_world);

	// �V�F�[�_�v���O�����̓ǂݍ��݂ƃR���p�C��
	LPD3DXBUFFER	errors = 0;
	D3DXCreateEffectFromFile(device, TEXT("..\\DX9Templete\\resource\\Shader\\light_diffuse.fx"), 0, 0, D3DXSHADER_DEBUG, 0, &m_pFX, &errors);
	if (errors) {
		return E_FAIL;
	}

	// �V�F�[�_�v���O�����փe�N�j�b�N�ւ̃n���h���̎擾
	m_hTech = m_pFX->GetTechniqueByName("BasicTech");

	// �V�F�[�_�[�v���O�����̃O���[�o���ϐ��̃n���h���̎擾
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

	// �e�N�j�b�N�̐ݒ�i�V�F�[�_�v���O�����̐ݒ�j
	m_pFX->SetTechnique(m_hTech);

	// �V�F�[�_�[�̃O���[�o���ϐ��̒l�̐ݒ�
	m_pFX->SetMatrix(m_hWorld, &m_world);
	D3DXMatrixInverse(&m_world_inv, NULL, &m_world);
	m_pFX->SetMatrix(m_hWorldInv, &m_world_inv);
	m_pFX->SetMatrix(m_hView, &m_view);
	m_pFX->SetMatrix(m_hProj, &m_projection);

	// ���C�g�̃x�N�g���̌v�Z
	D3DXVECTOR4		tmpLightDirection;
	tmpLightDirection.x = 0.5f;
	tmpLightDirection.y = 1.0f;
	tmpLightDirection.z = -2.0f;
	tmpLightDirection.w = 0.0f;
	D3DXVec4Normalize(&tmpLightDirection, &tmpLightDirection);
	m_pFX->SetVector(m_hLightDir, &tmpLightDirection);

	// �V�F�[�_�v���O�����̊J�n�錾
	m_pFX->Begin(0, 0);

	// X�t�@�C���̂̕`�揈��
	D3DXVECTOR4		tmpColor;

	// �}�e���A���������o��
	D3DXMATERIAL*	mD3DXMaterials = (D3DXMATERIAL*)m_pD3DXMtrlBuffer->GetBufferPointer();
	for (DWORD i = 0; i < m_numMtrl; i++) {

		if (m_pTextures[i] != 0) {
			m_pFX->BeginPass(0);
		}
		else {
			m_pFX->BeginPass(1);
		}

		m_pFX->SetTexture(m_hTexture, m_pTextures[i]);

		// �}�e���A���̃R�s�[
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

		// �������ꂽ���b�V���̕`��
		m_pMesh->DrawSubset(i);

		m_pFX->EndPass();
	}

	// �V�F�[�_�v���O�����̏I���錾
	m_pFX->End();
}

HRESULT MaterialMesh::LoadMeshFile(LPDIRECT3DDEVICE9 device)
{
	// �w�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(TEXT("..\\DX9Templete\\resource\\Mesh\\cube-tex01.X"),// �w�t�@�C���̃t�@�C����
		D3DXMESH_SYSTEMMEM,	// ���b�V�����V�X�e���������ɓW�J����
		device,			// D3D�f�o�C�X�I�u�W�F�N�g
		NULL,
		&m_pD3DXMtrlBuffer,	// �����o�b�t�@�̐ݒ�
		NULL,
		&m_numMtrl,			// �����̐�
		&m_pMesh))) {		// �i�[��̃��b�V��
		return E_FAIL;
	}

	// X�t�@�C���Ŏw�肳��Ă���e�N�X�`���t�@�C���̓ǂݍ���
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