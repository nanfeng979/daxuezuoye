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
	//���ö��������������



	//���ö������飬�������ÿ����������

	//�����������飬�������ÿ����������


	HRESULT result;
	D3D10_BUFFER_DESC vbd;
	vbd.Usage = D3D10_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(/* �˴�����Զ����ʽ�Ľṹ������ */) * /*�˴��������*/;
	vbd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D10_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = vertices;

	if (FAILED(pD3dDevice->CreateBuffer(/*�˴���������������ָ���鲹�룬����京��*/)))
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
	pD3dDevice->IASetPrimitiveTopology(/*ѡ�����ͼԪ��������*/);
	pD3dDevice->IASetInputLayout(mVertexLayout);

	pD3dDevice->DrawIndexed(/*����������������⺬��*/);
}

void Shape::buildVertexLayouts(ID3D10Device* pD3dDevice, ID3D10EffectTechnique*	pTech)
{
	// Create the vertex input layout.
	D3D10_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		/*��������Ԫ�أ����*/
	};
	// Create the input layout
	D3D10_PASS_DESC PassDesc;
	pTech->GetPassByIndex(0)->GetDesc(&PassDesc);
	pD3dDevice->CreateInputLayout(vertexDesc, 2, PassDesc.pIAInputSignature,
		PassDesc.IAInputSignatureSize, &mVertexLayout);
}

