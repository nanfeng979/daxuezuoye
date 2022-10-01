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

bool Shape::createTriangle(ID3D10Device* pD3dDevice)
{
	HRESULT hr = S_OK;
	mVertexCount = 3;
	mIndexCount = 3;

	ColorVertex vertices[] =
	{
		{ D3DXVECTOR3(0.0f, 1.0f, 1.0f), WHITE },
		{ D3DXVECTOR3(-0.70f, -0.70f, 1.0f), BLACK },
		{ D3DXVECTOR3(+0.70f, -0.70f, 1.0f), RED },
		
	};
	DWORD indices[] ={0, 2, 1,};
	HRESULT result;
	D3D10_BUFFER_DESC vbd;
	vbd.Usage = D3D10_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(ColorVertex) * mVertexCount;
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
	UINT stride = sizeof(ColorVertex);
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
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 }
	};
	// Create the input layout
	D3D10_PASS_DESC PassDesc;
	pTech->GetPassByIndex(0)->GetDesc(&PassDesc);
	pD3dDevice->CreateInputLayout(vertexDesc, 2, PassDesc.pIAInputSignature,
		PassDesc.IAInputSignatureSize, &mVertexLayout);
}

