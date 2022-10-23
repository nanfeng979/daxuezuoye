#include "LightTriPyramid.h"


LightTriPyramid::LightTriPyramid(ID3D10Device* device):ShapeClass(device)
{
}


LightTriPyramid::~LightTriPyramid(void)
{
}


bool LightTriPyramid::Initialize()
{
	mVertexCount = 12;
	mIndexCount = 12;

	VertexSize = sizeof(LightVertexType);
	
	LightVertexType vertices[] =
	{
		{D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(0.866f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(-0.866f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

		{D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(0.0f, 0.50f, 1.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(0.866f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

		{D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(-0.866f, -0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(0.0f, 0.50f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

		{D3DXVECTOR3(0.0f, 0.50f, 1.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(-0.866f, -0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(0.866f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
				
		
    };
	D3DXVECTOR3 out;
	this->ComputeNormal(vertices[0].position,vertices[1].position,vertices[2].position,out);
	vertices[0].normal = vertices[1].normal = vertices[2].normal = out;

	this->ComputeNormal(vertices[3].position,vertices[4].position,vertices[5].position,out);
	vertices[3].normal = vertices[4].normal = vertices[5].normal = out;

	this->ComputeNormal(vertices[6].position,vertices[7].position,vertices[8].position,out);
	vertices[6].normal = vertices[7].normal = vertices[8].normal = out;

	this->ComputeNormal(vertices[9].position,vertices[10].position,vertices[11].position,out);
	vertices[9].normal = vertices[10].normal = vertices[11].normal = out;
	
	DWORD indices[]=
	{
		
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11,

	};
	
	HRESULT result;


	
	D3D10_BUFFER_DESC vbd;
	vbd.Usage = D3D10_USAGE_IMMUTABLE; 
	vbd.ByteWidth = sizeof(LightVertexType) * mVertexCount; 
	vbd.BindFlags = D3D10_BIND_VERTEX_BUFFER; 
	vbd.CPUAccessFlags = 0; 
	vbd.MiscFlags = 0;  
	D3D10_SUBRESOURCE_DATA vinitData; 
	vinitData.pSysMem = vertices;

	if(FAILED(mD3DDevice->CreateBuffer( &vbd,&vinitData,&mVertexBuffer)))
	{
		return false;
	}

	D3D10_BUFFER_DESC ibd;
	ibd.Usage = D3D10_USAGE_IMMUTABLE; 
	ibd.ByteWidth = sizeof(DWORD) * mIndexCount; 
	ibd.BindFlags = D3D10_BIND_INDEX_BUFFER; 
	ibd.CPUAccessFlags = 0; 
	ibd.MiscFlags = 0;  
	D3D10_SUBRESOURCE_DATA iinitData; 
	iinitData.pSysMem = indices;

	if(FAILED(mD3DDevice->CreateBuffer( &ibd,&iinitData,&mIndexBuffer)))
	{
		return false;
	}

	return true;
}