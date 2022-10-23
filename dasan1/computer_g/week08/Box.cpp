#include "Box.h"


Box::Box(ID3D10Device* device) :ShapeClass(device)
{
}


Box::~Box(void)
{
}

float d = 2.0f;

bool Box::Initialize()
{
	mVertexCount = 36;
	mIndexCount = 36;

	VertexSize = sizeof(LightVertexType);

	LightVertexType vertices[] =
	{
		// 正面
		{D3DXVECTOR3(0.5f + d, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,0.0f,0.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(0.5f + d, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,0.0f,0.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(-0.5f + d, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,0.0f,0.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

		{D3DXVECTOR3(-0.5f + d, -0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,0.0f,0.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(-0.5f + d, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f,0.0f,0.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(0.5f + d, 0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,0.0f,0.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

		// 右面
		{D3DXVECTOR3(0.5f + d, -0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(0.5f + d, 0.50f, 0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(0.5f + d, -0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

		{D3DXVECTOR3(0.5f + d, -0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(0.5f + d, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(0.5f + d, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

		// 左面
		{D3DXVECTOR3(-0.5f + d, -0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(-0.5f + d, -0.5f, 0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(-0.5f + d, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

		{D3DXVECTOR3(-0.5f + d, -0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(-0.5f + d, 0.5f, 0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(-0.5f + d, 0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

		// 上面
		{D3DXVECTOR3(-0.5f + d, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(-0.5f + d, 0.5f, 0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(0.5f + d, 0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

		{D3DXVECTOR3(0.5f + d, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(-0.5f + d, 0.5f, 0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(0.5f + d, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

		// 下面
		{D3DXVECTOR3(-0.5f + d, -0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(0.5f + d, -0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(-0.5f + d, -0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

		{D3DXVECTOR3(-0.5f + d, -0.5f, 0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(0.5f + d, -0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(0.5f + d, -0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

		// 背面
		{D3DXVECTOR3(0.5f + d, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(-0.5f + d, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(0.5f + d, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},

		{D3DXVECTOR3(0.5f + d, -0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(-0.5f + d, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
		{D3DXVECTOR3(-0.5f + d, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXCOLOR(1.0f,0.5f,0.2f,30.0f)},
	};
	D3DXVECTOR3 out;
	/*// 正面
	this->ComputeNormal(vertices[0].position, vertices[1].position, vertices[2].position, out);
	vertices[0].normal = vertices[1].normal = vertices[2].normal = out;

	this->ComputeNormal(vertices[3].position, vertices[4].position, vertices[5].position, out);
	vertices[3].normal = vertices[4].normal = vertices[5].normal = out;

	// 右面
	this->ComputeNormal(vertices[6].position, vertices[7].position, vertices[8].position, out);
	vertices[6].normal = vertices[7].normal = vertices[8].normal = out;

	this->ComputeNormal(vertices[9].position, vertices[10].position, vertices[11].position, out);
	vertices[9].normal = vertices[10].normal = vertices[11].normal = out;

	// 左面
	this->ComputeNormal(vertices[12].position, vertices[13].position, vertices[14].position, out);
	vertices[12].normal = vertices[13].normal = vertices[14].normal = out;

	this->ComputeNormal(vertices[15].position, vertices[16].position, vertices[17].position, out);
	vertices[15].normal = vertices[16].normal = vertices[17].normal = out;

	// 上面
	this->ComputeNormal(vertices[18].position, vertices[19].position, vertices[20].position, out);
	vertices[18].normal = vertices[19].normal = vertices[20].normal = out;

	this->ComputeNormal(vertices[21].position, vertices[22].position, vertices[23].position, out);
	vertices[21].normal = vertices[22].normal = vertices[23].normal = out;

	// 下面
	this->ComputeNormal(vertices[24].position, vertices[25].position, vertices[26].position, out);
	vertices[24].normal = vertices[25].normal = vertices[26].normal = out;

	this->ComputeNormal(vertices[27].position, vertices[28].position, vertices[29].position, out);
	vertices[27].normal = vertices[28].normal = vertices[29].normal = out;

	// 背面
	this->ComputeNormal(vertices[30].position, vertices[31].position, vertices[32].position, out);
	vertices[30].normal = vertices[31].normal = vertices[32].normal = out;

	this->ComputeNormal(vertices[33].position, vertices[34].position, vertices[35].position, out);
	vertices[33].normal = vertices[34].normal = vertices[35].normal = out;*/

	for (int i = 0; i < 36; i += 3)
	{
		this->ComputeNormal(vertices[i].position, vertices[i+1].position, vertices[i+2].position, out);
		vertices[i].normal = vertices[i+1].normal = vertices[i+2].normal = out;
	}

	DWORD indices[] =
	{

		0, 1, 2, // 正面
		3, 4, 5,

		6, 7, 8, // 右面
		9, 10, 11,

		12, 13, 14, // 左面
		15, 16, 17,
		
		18, 19, 20, // 上面
		21, 22, 23,
		
		24, 25, 26, // 下面
		27, 28, 29,
		
		30, 31, 32, // 背面
		33, 34, 35,

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
	iinitData.pSysMem = indices;

	if (FAILED(mD3DDevice->CreateBuffer(&ibd, &iinitData, &mIndexBuffer)))
	{
		return false;
	}

	return true;
}