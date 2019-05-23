#pragma once
#include "stddef.h"
#include <d3d9.h>
#include <d3dx9.h>

class Camera
{
private:
	IDirect3DDevice9* pDevice;
	D3DXVECTOR3 m_Position;
	D3DXQUATERNION m_Rotation;
	D3DXMATRIX m_View;
	D3DXMATRIX m_Projection;

	float mRotation;
public:
	Camera(IDirect3DDevice9* device);
	~Camera();
	void SetMatrices();
	void SetView(const D3DXVECTOR3& inPosition, const D3DXVECTOR3& inRotation);
	void SetViewLookAt(const D3DXVECTOR3& inEye, const D3DXVECTOR3& inAt, const float inRoll);
	void SetProjectionPerspective(const float inFovY, const float inWidth, const float inHeight, const float inNear, const float inFar);

	void Update();
};

