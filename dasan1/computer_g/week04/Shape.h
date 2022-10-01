#pragma once
#include <D3D10.h>
#include <D3DX10.h>
class Shape
{
private:
	struct ColorVertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR4 color;
	};

public:
	Shape();
	~Shape();

	bool createTriangle(ID3D10Device* pD3dDevice);
	void onFrameRender(ID3D10Device* pD3dDevice);

	void buildVertexLayouts(ID3D10Device* pD3dDevice, ID3D10EffectTechnique* pTech);

private:
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


