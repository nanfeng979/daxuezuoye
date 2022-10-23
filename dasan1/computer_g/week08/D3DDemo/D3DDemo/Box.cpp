#include "Box.h"


Box::Box(ID3D10Device* device) :ShapeClass(device)
{
}


Box::~Box(void)
{
}



bool Box::Initialize()
{
	float d = distance;
	TexVertexType init_data = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mVertexCount = 24;
	mIndexCount = 36;

	//VertexSize = sizeof(LightVertexType);

	//LightVertexType vertices[] =
	//{
	//	// 正面
	//	{D3DXVECTOR3(0.5f + d, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,0.0f,0.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(0.5f + d, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,0.0f,0.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(-0.5f + d, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,0.0f,0.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

	//	{D3DXVECTOR3(-0.5f + d, -0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,0.0f,0.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(-0.5f + d, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f,0.0f,0.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(0.5f + d, 0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,0.0f,0.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

	//	// 右面
	//	{D3DXVECTOR3(0.5f + d, -0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(0.5f + d, 0.50f, 0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(0.5f + d, -0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

	//	{D3DXVECTOR3(0.5f + d, -0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(0.5f + d, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(0.5f + d, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

	//	// 左面
	//	{D3DXVECTOR3(-0.5f + d, -0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(-0.5f + d, -0.5f, 0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(-0.5f + d, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

	//	{D3DXVECTOR3(-0.5f + d, -0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(-0.5f + d, 0.5f, 0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(-0.5f + d, 0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

	//	// 上面
	//	{D3DXVECTOR3(-0.5f + d, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(-0.5f + d, 0.5f, 0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(0.5f + d, 0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

	//	{D3DXVECTOR3(0.5f + d, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(-0.5f + d, 0.5f, 0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(0.5f + d, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

	//	// 下面
	//	{D3DXVECTOR3(-0.5f + d, -0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(0.5f + d, -0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(-0.5f + d, -0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

	//	{D3DXVECTOR3(-0.5f + d, -0.5f, 0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(0.5f + d, -0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(0.5f + d, -0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

	//	// 背面
	//	{D3DXVECTOR3(0.5f + d, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(-0.5f + d, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(0.5f + d, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

	//	{D3DXVECTOR3(0.5f + d, -0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(-0.5f + d, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//	{D3DXVECTOR3(-0.5f + d, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	//};
	//D3DXVECTOR3 out;

	//for (int i = 0; i < 36; i += 3)
	//{
	//	this->ComputeNormal(vertices[i].position, vertices[i+1].position, vertices[i+2].position, out);
	//	vertices[i].normal = vertices[i+1].normal = vertices[i+2].normal = out;
	//}

	//DWORD indices[] =
	//{

	//	0, 1, 2, // 正面
	//	3, 4, 5,

	//	6, 7, 8, // 右面
	//	9, 10, 11,

	//	12, 13, 14, // 左面
	//	15, 16, 17,
	//	
	//	18, 19, 20, // 上面
	//	21, 22, 23,
	//	
	//	24, 25, 26, // 下面
	//	27, 28, 29,
	//	
	//	30, 31, 32, // 背面
	//	33, 34, 35,

	//};
	VertexSize = sizeof(TexVertexType);

	TexVertexType v[24];
/*
	v[0] = TexVertexType(-1.0f + d, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[1] = TexVertexType(-1.0f + d, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[2] = TexVertexType(1.0f + d, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[3] = TexVertexType(1.0f + d, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	// Fill in the back face vertex data.
	v[4] = TexVertexType(-1.0f + d, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	v[5] = TexVertexType(1.0f + d, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	v[6] = TexVertexType(1.0f + d, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	v[7] = TexVertexType(-1.0f + d, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	// Fill in the top face vertex data.
	v[8] = TexVertexType(-1.0f + d, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	v[9] = TexVertexType(-1.0f + d, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	v[10] = TexVertexType(1.0f + d, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	v[11] = TexVertexType(1.0f + d, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the bottom face vertex data.
	v[12] = TexVertexType(-1.0f + d, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);
	v[13] = TexVertexType(1.0f + d, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
	v[14] = TexVertexType(1.0f + d, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
	v[15] = TexVertexType(-1.0f + d, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

	// Fill in the left face vertex data.
	v[16] = TexVertexType(-1.0f + d, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[17] = TexVertexType(-1.0f + d, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[18] = TexVertexType(-1.0f + d, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[19] = TexVertexType(-1.0f + d, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the right face vertex data.
	v[20] = TexVertexType(1.0f + d, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[21] = TexVertexType(1.0f + d, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[22] = TexVertexType(1.0f + d, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[23] = TexVertexType(1.0f + d, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	*/

	/*if (zhengmian != init_data) {
		v[0] = TexVertexType(-1.0f + d, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
		v[1] = TexVertexType(-1.0f + d, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
		v[2] = TexVertexType(1.0f + d, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
		v[3] = TexVertexType(1.0f + d, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
	}

	if (shangmian != init_data) {
		v[8] = TexVertexType(-1.0f + d, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v[9] = TexVertexType(-1.0f + d, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		v[10] = TexVertexType(1.0f + d, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
		v[11] = TexVertexType(1.0f + d, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);
	}*/

	if (zhengmian)
	{
		v[0] = TexVertexType(-1.0f + d, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
		v[1] = TexVertexType(-1.0f + d, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
		v[2] = TexVertexType(1.0f + d, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
		v[3] = TexVertexType(1.0f + d, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
	}
	if (shangmian) {
		v[8] = TexVertexType(-1.0f + d, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		v[9] = TexVertexType(-1.0f + d, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		v[10] = TexVertexType(1.0f + d, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
		v[11] = TexVertexType(1.0f + d, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);
	}


	DWORD i[36];

	// Fill in the front face index data
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	// Fill in the back face index data
	i[6] = 4; i[7] = 5; i[8] = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	// Fill in the top face index data
	i[12] = 8; i[13] = 9; i[14] = 10;
	i[15] = 8; i[16] = 10; i[17] = 11;

	// Fill in the bottom face index data
	i[18] = 12; i[19] = 13; i[20] = 14;
	i[21] = 12; i[22] = 14; i[23] = 15;

	// Fill in the left face index data
	i[24] = 16; i[25] = 17; i[26] = 18;
	i[27] = 16; i[28] = 18; i[29] = 19;

	// Fill in the right face index data
	i[30] = 20; i[31] = 21; i[32] = 22;
	i[33] = 20; i[34] = 22; i[35] = 23;

	HRESULT result;



	D3D10_BUFFER_DESC vbd;
	vbd.Usage = D3D10_USAGE_IMMUTABLE;
	//vbd.ByteWidth = sizeof(LightVertexType) * mVertexCount;
	vbd.ByteWidth = sizeof(TexVertexType) * mVertexCount;
	vbd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D10_SUBRESOURCE_DATA vinitData;
	
	vinitData.pSysMem = v;

	if (FAILED(mD3DDevice->CreateBuffer(&vbd, &vinitData, &mVertexBuffer)))
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
	iinitData.pSysMem = i;

	if (FAILED(mD3DDevice->CreateBuffer(&ibd, &iinitData, &mIndexBuffer)))
	{
		return false;
	}

	

	return true;
}