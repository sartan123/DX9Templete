#include "Camera.h"



Camera::Camera(IDirect3DDevice9* device)
: pDevice(device)
, mRotation(0.0f)
{
	pDevice->AddRef();
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	D3DXMatrixIdentity(&m_View);
	pDevice->SetTransform(D3DTS_VIEW, &m_View);

	D3DXMatrixIdentity(&m_Projection);
	pDevice->SetTransform(D3DTS_PROJECTION, &m_Projection);
}


Camera::~Camera()
{
	pDevice->Release();
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
	D3DXQuaternionRotationAxis(&rot_z, &D3DXVECTOR3(1.0f, 0.0f, 1.0f), D3DXToRadian(inRotation.z));
	m_Rotation = rot_x * rot_y * rot_y;

	m_View._41 = D3DXVec3Dot(&D3DXVECTOR3(m_View._11, m_View._12, m_View._13), &m_Position);
	m_View._42 = D3DXVec3Dot(&D3DXVECTOR3(m_View._21, m_View._22, m_View._23), &m_Position);
	m_View._43 = D3DXVec3Dot(&D3DXVECTOR3(m_View._31, m_View._32, m_View._33), &m_Position);

	pDevice->SetTransform(D3DTS_VIEW, &m_View);
}

void Camera::SetViewLookAt(const D3DXVECTOR3& inEye, const D3DXVECTOR3& inAt, const float inRoll)
{
	D3DXVECTOR3 up = D3DXVECTOR3(sinf(D3DXToRadian(inRoll)), cosf(D3DXToRadian(inRoll)), 0.0f);
	D3DXMatrixLookAtLH(&m_View, &inEye, &inAt, &up);
	pDevice->SetTransform(D3DTS_VIEW, &m_View);
	m_Position = inEye;
	D3DXQuaternionRotationMatrix(&m_Rotation, &m_View);
}

void Camera::SetProjectionPerspective(const float inFovY, const float inWidth, const float inHeight, const float inNear, const float inFar)
{
	D3DXMatrixPerspectiveFovLH(&m_Projection, D3DXToRadian(inFovY), inWidth / inHeight, inNear, inFar);
	pDevice->SetTransform(D3DTS_PROJECTION, &m_Projection);
}

void Camera::Update()
{
	mRotation += 1.0f;
	SetViewLookAt(D3DXVECTOR3(0.0f, 1.0f, -5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), mRotation);
}