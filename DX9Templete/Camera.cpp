#include "Camera.h"



Camera::Camera(IDirect3DDevice9* device)
: pDevice(device)
, mRotation(0.0f)
, mZRotDef(0.0f)
, mIsNeedUpdate(false)
{
	pDevice->AddRef();
	m_Position = D3DXVECTOR3(0.0f, 1.0f, -3.0f);
	m_Eye = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 up = D3DXVECTOR3(0, 1, 0);
	D3DXMatrixLookAtLH(&m_View, &m_Position, &m_Eye, &up);
	pDevice->SetTransform(D3DTS_VIEW, &m_View);

	D3DXMatrixIdentity(&m_Projection);
	pDevice->SetTransform(D3DTS_PROJECTION, &m_Projection);

	SetLight();
}


Camera::~Camera()
{
	pDevice->Release();
}

void Camera::SetLight()
{
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
}

void Camera::SetMatrices()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixRotationY(&matWorld, timeGetTime() / 1000.0f);
	pDevice->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	pDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void Camera::SetView(const D3DXVECTOR3& inPosition, const D3DXVECTOR3& inRotation)
{
	m_Position = inPosition;

	D3DXQUATERNION rot_x, rot_y, rot_z;
	D3DXQuaternionRotationAxis(&rot_x, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXToRadian(inRotation.x));
	D3DXQuaternionRotationAxis(&rot_y, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(inRotation.y));
	D3DXQuaternionRotationAxis(&rot_z, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXToRadian(inRotation.z));
	m_Rotation = rot_x * rot_y * rot_y;

	m_View._41 = D3DXVec3Dot(&D3DXVECTOR3(m_View._11, m_View._12, m_View._13), &m_Position);
	m_View._42 = D3DXVec3Dot(&D3DXVECTOR3(m_View._21, m_View._22, m_View._23), &m_Position);
	m_View._43 = D3DXVec3Dot(&D3DXVECTOR3(m_View._31, m_View._32, m_View._33), &m_Position);

	pDevice->SetTransform(D3DTS_VIEW, &m_View);
}

void Camera::SetViewLookAt(const D3DXVECTOR3& inEye, const D3DXVECTOR3& inAt, const float inRoll)
{
	D3DXVECTOR3 up = D3DXVECTOR3(0, 1, 0);
	D3DXMatrixLookAtLH(&m_View, &m_Position, &m_Eye, &up);
	pDevice->SetTransform(D3DTS_VIEW, &m_View);
	D3DXQuaternionRotationMatrix(&m_Rotation, &m_View);
}

void Camera::SetProjectionPerspective(const float inFovY, const float inWidth, const float inHeight, const float inNear, const float inFar)
{
	D3DXMatrixPerspectiveFovLH(&m_Projection, D3DXToRadian(inFovY), inWidth / inHeight, inNear, inFar);
	pDevice->SetTransform(D3DTS_PROJECTION, &m_Projection);
}

void Camera::Update()
{
	if (!mIsNeedUpdate) return;
	D3DXMATRIX ZRotMatV;
	D3DXMatrixRotationZ(&ZRotMatV, mZRotDef);
	m_Projection = ZRotMatV * m_Projection;

	D3DXVECTOR3 DL;
	D3DXVec3TransformCoord(&DL, &m_DirDef, &m_Projection);
	if (DL.x != 0.0f || DL.y != 0.0f || DL.z != 0.0f) {
		D3DXVECTOR3 RotAxis;
		D3DXVECTOR3* camZAxis = (D3DXVECTOR3*)m_Projection.m[2];
		D3DXVec3Cross(&RotAxis, &DL, camZAxis);

		D3DXQUATERNION TransQ;
		D3DXQuaternionRotationAxis(&TransQ, &RotAxis, 0.02f);
		D3DXMATRIX TransRotMat;
		D3DXMatrixRotationQuaternion(&TransRotMat, &TransQ);
		D3DXVec3TransformCoord(&m_Position, &m_Position, &TransRotMat);

		// ③ 移動後カメラ姿勢更新
		D3DXVECTOR3 X, Y, Z;

		Z = -m_Position;
		D3DXVec3Normalize(&Z, &Z);

		memcpy(&Y, m_Projection.m[1], sizeof(D3DXVECTOR3));
		D3DXVec3Cross(&X, &Y, &Z);
		D3DXVec3Normalize(&X, &X);

		D3DXVec3Cross(&Y, &Z, &X);
		D3DXVec3Normalize(&Y, &Y);

		D3DXMatrixIdentity(&m_Projection);
		memcpy(m_Projection.m[0], &X, sizeof(D3DXVECTOR3));
		memcpy(m_Projection.m[1], &Y, sizeof(D3DXVECTOR3));
		memcpy(m_Projection.m[2], &Z, sizeof(D3DXVECTOR3));
	}
	float m_distance = D3DXVec3Length(&m_Position);
	if (m_distance - mOffsetZ > 0) {
		D3DXVECTOR3 Z = -m_Position;
		D3DXVec3Normalize(&Z, &Z);
		m_Position += mOffsetZ * Z;
		m_distance -= mOffsetZ;
	}


	// ⑤ ビュー行列更新
	D3DXVECTOR3 posW = m_Position + m_Eye;
	memcpy(&m_View, &m_Projection, sizeof(D3DXMATRIX));
	memcpy(&m_View.m[3], &posW, sizeof(D3DXVECTOR3));
	m_View._44 = 1.0f;
	D3DXMatrixInverse(&m_View, 0, &m_View);

	mIsNeedUpdate = false;

	ResetDefValue();
	pDevice->SetTransform(D3DTS_VIEW, &m_View);
}

void Camera::MovePositionX(float x)
{
	m_DirDef.x += x;
	mIsNeedUpdate = true;
}

void Camera::MovePositionY(float y)
{
	m_DirDef.y += y;
	mIsNeedUpdate = true;
}

void Camera::ResetDefValue() {
	memset(&m_DirDef, 0, sizeof(D3DXVECTOR3));
	mZRotDef = 0;
	mOffsetZ = 0;
}