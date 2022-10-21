#include "TriPyramid.h"


TriPyramid::TriPyramid(ID3D10Device* device):ShapeClass(device)
{
}


TriPyramid::~TriPyramid(void)
{
}

bool TriPyramid::Initialize()
{
	mVertexCount = 4;
	mIndexCount = 12;

	VertexSize = sizeof(VertexType);

	VertexType vertices[] =
	{
		{D3DXVECTOR3(0.0f, 1.0f, 0.0f), RED},
		{D3DXVECTOR3(0.0f, 0.50f, 1.0f), WHITE},
		{D3DXVECTOR3(-0.866f, -0.5f, -0.5f), WHITE},
		{D3DXVECTOR3(0.866f, -0.5f, -0.5f), WHITE},
		//{D3DXVECTOR3(-1.0f, -1.0f, -1.0f), WHITE},
		//{D3DXVECTOR3(-1.0f, +1.0f, -1.0f), BLACK},
		//{D3DXVECTOR3(+1.0f, +1.0f, -1.0f), RED},
		//{D3DXVECTOR3(+1.0f, -1.0f, -1.0f), GREEN},
		//{D3DXVECTOR3(-1.0f, -1.0f, +1.0f), BLUE},
		//{D3DXVECTOR3(-1.0f, +1.0f, +1.0f), YELLOW},
		//{D3DXVECTOR3(+1.0f, +1.0f, +1.0f), CYAN},
		//{D3DXVECTOR3(+1.0f, -1.0f, +1.0f), MAGENTA},
    };

	//DWORD indices[]=
	//{
	//	// front face
	//	0, 1, 2,
	//	0, 2, 3,

	//	// back face
	//	4, 6, 5,
	//	4, 7, 6,

	//	// left face
	//	4, 5, 1,
	//	4, 1, 0,

	//	// right face
	//	3, 2, 6,
	//	3, 6, 7,

	//	// top face
	//	1, 5, 6,
	//	1, 6, 2,

	//	// bottom face
	//	4, 0, 3, 
	//	4, 3, 7
	//};
	DWORD indices[]=
	{
		
		0, 3, 2,
		0, 1, 3,
		0, 2, 1,
		1, 2, 3,

	};
	
	HRESULT result;


	
	D3D10_BUFFER_DESC vbd;
	vbd.Usage = D3D10_USAGE_IMMUTABLE; 
	vbd.ByteWidth = sizeof(VertexType) * mVertexCount; 
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