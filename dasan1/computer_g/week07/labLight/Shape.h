#pragma once
#include <D3D10.h>
#include <D3DX10.h>
class Shape
{
private:
	struct ColorVertex
	{
		D3DXVECTOR3 position;
		D3DXCOLOR color;
	};

	struct LightVertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
		D3DXCOLOR diffuse;
		D3DXCOLOR spec;
	};

public:
	Shape();
	~Shape();


	bool createTriangle(ID3D10Device* pD3dDevice);
	bool createTriPyramid(ID3D10Device* pD3dDevice);
	//bool createLightTriangle(ID3D10Device* pD3dDevice);

	void onFrameRender(ID3D10Device* pD3dDevice);

	void buildVertexLayouts(ID3D10Device* pD3dDevice, ID3D10EffectTechnique* pTech);

private:
	void ComputeNormal(const D3DXVECTOR3& p0, const D3DXVECTOR3& p1, const D3DXVECTOR3& p2, D3DXVECTOR3& out);

	ID3D10Buffer *mVertexBuffer, *mIndexBuffer;
	ID3D10InputLayout*		mVertexLayout;
	int mVertexCount, mIndexCount;

	

};
const D3DXCOLOR WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR RED(1.0f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR GREEN(0.0f, 1.0f, 0.0f, 1.0f);
const D3DXCOLOR BLUE(0.0f, 0.0f, 1.0f, 1.0f);
const D3DXCOLOR YELLOW(1.0f, 1.0f, 0.0f, 1.0f);
const D3DXCOLOR CYAN(0.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR MAGENTA(1.0f, 0.0f, 1.0f, 1.0f);


