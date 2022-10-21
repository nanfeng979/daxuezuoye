#pragma once

#include <D3D10.h>
#include <D3DX10.h>
	
class ShapeClass
{
protected:

	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR4 color;
	};

	struct LightVertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
		D3DXCOLOR   diffuse;
		D3DXCOLOR	spec;
	};

public:
	ShapeClass(ID3D10Device*);
	~ShapeClass(void);

	virtual bool Initialize()=0;
	void Shutdown();
	void Render();


	int GetIndexCount();

	void Move(D3DXVECTOR3 d);
	void Rotate(D3DXVECTOR3 a);
	void Zoom(float s);

	void UpdateMatrix();
	D3DXMATRIX GetWorldMatrix();

protected:
	void ComputeNormal(const D3DXVECTOR3& p0,const D3DXVECTOR3& p1,const D3DXVECTOR3& p2,D3DXVECTOR3& out);
	UINT VertexSize;


	ID3D10Device* mD3DDevice;
	ID3D10Buffer *mVertexBuffer,*mIndexBuffer;
	int mVertexCount,mIndexCount;

	D3DXMATRIX		worldMat,tranMat,rotXMat,rotYMat,rotZMat,zoomMat;

	D3DXVECTOR3		pos;
	D3DXVECTOR3		angle;
	float			scale;
};

const D3DXCOLOR WHITE(1.0f, 1.0f, 1.0f, 1.0f); 
const D3DXCOLOR BLACK(0.0f, 0.0f, 0.0f, 1.0f); 
const D3DXCOLOR RED(1.0f, 0.0f, 0.0f, 1.0f); 
const D3DXCOLOR GREEN(0.0f, 1.0f, 0.0f, 1.0f); 
const D3DXCOLOR BLUE(0.0f, 0.0f, 1.0f, 1.0f); 
const D3DXCOLOR YELLOW(1.0f, 1.0f, 0.0f, 1.0f); 
const D3DXCOLOR CYAN(0.0f, 1.0f, 1.0f, 1.0f); 
const D3DXCOLOR MAGENTA(1.0f, 0.0f, 1.0f, 1.0f); 

const D3DXCOLOR BEACH_SAND(1.0f, 0.96f, 0.62f, 1.0f);
const D3DXCOLOR LIGHT_YELLOW_GREEN(0.48f, 0.77f, 0.46f, 1.0f);
const D3DXCOLOR DARK_YELLOW_GREEN(0.1f, 0.48f, 0.19f, 1.0f);
const D3DXCOLOR DARKBROWN(0.45f, 0.39f, 0.34f, 1.0f);
	
