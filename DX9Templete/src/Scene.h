#include "stddef.h"
#include "Square.h"
#include "BasicTexture.h"
#include "MultiTexture.h"
#include "MaterialMesh.h"
#include "Particle.h"
#include "Camera.h"
#include "InputDevice.h"
#include <d3d9.h>
#include <d3dx9.h>

class Scene {
public:
	Scene();
	~Scene();

	void Destroy();
	HRESULT Create(LPDIRECT3DDEVICE9 device, HINSTANCE hInstance, HWND hwnd);
	void Draw(LPDIRECT3DDEVICE9 device);
	void UpdateInput();
private:
	InputDevice* mInput;
	float mInterval;

	Square *mSquare;
	TrianglePolygon *mTriangle;
	BasicTexture *mTexture;
	MultiTexture * mMultiTexture;
	MaterialMesh *mMesh;
	Particle	*mParticle;
	Camera		*mCamera;
};