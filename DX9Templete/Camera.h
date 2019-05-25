#pragma once
#include "stddef.h"
#include <d3d9.h>
#include <d3dx9.h>

class Camera
{
private:
	D3DLIGHT9 light;
	IDirect3DDevice9* pDevice;
	D3DXVECTOR3 m_Position; // カメラ座標
	D3DXVECTOR3 m_Eye; // 注視点
	D3DXQUATERNION m_Rotation;
	D3DXMATRIX m_View;
	D3DXMATRIX m_Projection;
	float mRotation;
	bool  mIsNeedUpdate;

	D3DXVECTOR3 m_DirDef; // 移動方向ベクトル
	float mZRotDef;
	float mOffsetZ;
public:
	Camera(IDirect3DDevice9* device);
	~Camera();
	void SetMatrices();
	void SetView(const D3DXVECTOR3& inPosition, const D3DXVECTOR3& inRotation);
	void SetViewLookAt(const D3DXVECTOR3& inEye, const D3DXVECTOR3& inAt, const float inRoll);
	void SetProjectionPerspective(const float inFovY, const float inWidth, const float inHeight, const float inNear, const float inFar);
	void MovePositionX(float x);
	void MovePositionY(float y);
	void Update();
	void ResetDefValue();
	void SetLight();
};

