#include "Shape.h"

Shape::Shape()
{
	mVertexCount = 0;
	mIndexCount = 0;
	mVertexBuffer = 0;
	mIndexBuffer = 0;
}

Shape::~Shape()
{
	if (mIndexBuffer)
	{
		mIndexBuffer->Release();
		mIndexBuffer = 0;
	}
	if (mVertexBuffer)
	{
		mVertexBuffer->Release();
		mVertexBuffer = 0;
	}
}

bool Shape::createTriPyramid(ID3D10Device* mD3DDevice)
{
	mVertexCount = 12;
	mIndexCount = 12;

	//VertexSize = sizeof(LightVertexType);

	LightVertex vertices[] =
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
	
	this->ComputeNormal(vertices[0].position, vertices[1].position, vertices[2].position, out);
	vertices[0].normal = vertices[1].normal = vertices[2].normal = out;

	this->ComputeNormal(vertices[3].position, vertices[4].position, vertices[5].position, out);
	vertices[3].normal = vertices[4].normal = vertices[5].normal = out;

	this->ComputeNormal(vertices[6].position, vertices[7].position, vertices[8].position, out);
	vertices[6].normal = vertices[7].normal = vertices[8].normal = out;

	this->ComputeNormal(vertices[9].position, vertices[10].position, vertices[11].position, out);
	vertices[9].normal = vertices[10].normal = vertices[11].normal = out;

	DWORD indices[] =
	{

		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11,

	};

	HRESULT result;



	D3D10_BUFFER_DESC vbd;
	vbd.Usage = D3D10_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(LightVertex) * mVertexCount;
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
bool Shape::createTriangle(ID3D10Device* pD3dDevice)
{
	HRESULT hr = S_OK;
	mVertexCount = 3;
	mIndexCount = 3;

	LightVertex vertices[] =
	{
		{ D3DXVECTOR3(0.0f, 1.0f, 1.0f), D3DXVECTOR3(0,0,-1),WHITE,WHITE },
		{ D3DXVECTOR3(-0.70f, -0.70f, 1.0f), D3DXVECTOR3(0,0,-1),WHITE,WHITE },
		{ D3DXVECTOR3(+0.70f, -0.70f, 1.0f), D3DXVECTOR3(0,0,-1),WHITE,WHITE },
		
	};
	DWORD indices[] ={0, 2, 1,};
	HRESULT result;
	D3D10_BUFFER_DESC vbd;
	vbd.Usage = D3D10_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(LightVertex) * mVertexCount;
	vbd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D10_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = vertices;

	if (FAILED(pD3dDevice->CreateBuffer(&vbd, &vinitData, &mVertexBuffer)))
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

	if (FAILED(pD3dDevice->CreateBuffer(&ibd, &iinitData, &mIndexBuffer)))
	{
		return false;
	}	

	
	return true;	
}

void Shape::onFrameRender(ID3D10Device* pD3dDevice)
{
	UINT stride = sizeof(LightVertex);
	UINT offset = 0;
	pD3dDevice->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	pD3dDevice->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	pD3dDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pD3dDevice->IASetInputLayout(mVertexLayout);

	pD3dDevice->DrawIndexed(mIndexCount, 0, 0);
}

void Shape::buildVertexLayouts(ID3D10Device* pD3dDevice, ID3D10EffectTechnique*	pTech)
{
	// Create the vertex input layout.
	D3D10_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
0, D3D10_INPUT_PER_VERTEX_DATA, 0},
{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
12, D3D10_INPUT_PER_VERTEX_DATA, 0},
{"DIFFUSE", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,
24, D3D10_INPUT_PER_VERTEX_DATA, 0},
{"SPECULAR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,40, D3D10_INPUT_PER_VERTEX_DATA, 0}

	};
	// Create the input layout
	D3D10_PASS_DESC PassDesc;
	pTech->GetPassByIndex(0)->GetDesc(&PassDesc);
	pD3dDevice->CreateInputLayout(vertexDesc,4, PassDesc.pIAInputSignature,
		PassDesc.IAInputSignatureSize, &mVertexLayout);
}


void Shape::ComputeNormal(const D3DXVECTOR3& p0, 
	const D3DXVECTOR3& p1, const D3DXVECTOR3& p2, 
	D3DXVECTOR3& out)
{
	D3DXVECTOR3 u = p1 - p0;
	D3DXVECTOR3 v = p2 - p0;
	D3DXVec3Cross(&out, &u, &v);
	D3DXVec3Normalize(&out, &out);
}

