#include "stddef.h"
#include "Square.h"
#include "BasicTexture.h"
#include <d3d9.h>
#include <d3dx9.h>

class Scene {
public:
	Scene();
	~Scene();

	void Destroy();
	HRESULT Create(LPDIRECT3DDEVICE9 device);
	void Draw(LPDIRECT3DDEVICE9 device);
private:
	Square *mSquare;
	TrianglePolygon *mTriangle;
	BasicTexture *mTexture;
};