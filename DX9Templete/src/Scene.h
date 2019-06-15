#include "stddef.h"
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
	D3DXMATRIX mProjection;
	D3DXMATRIX mView;

	struct VERTEX_POS {
		D3DXVECTOR3	p;
	};
	struct VERTEX_COLOR {
		D3DXVECTOR4	color;
	};

	LPDIRECT3DVERTEXDECLARATION9 mVertexDec;
	LPDIRECT3DVERTEXBUFFER9	mVertexBuffer;
	LPDIRECT3DVERTEXBUFFER9	mVertexColorBuffer;

	LPD3DXEFFECT	mEffect;
	D3DXHANDLE	mTechHandle;

	D3DXHANDLE	mWvpHandle;
	D3DXHANDLE	mColorHandle;
};