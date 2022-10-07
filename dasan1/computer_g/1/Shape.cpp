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
	//设置顶点和索引的数量



	//设置顶点数组，填充其中每个顶点数据

	//设置索引数组，填充其中每个索引数据


	HRESULT result;
	D3D10_BUFFER_DESC vbd;
	vbd.Usage = D3D10_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(/* 此处填顶点自定义格式的结构体类型 */) * /*此处填顶点数量*/;
	vbd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D10_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = vertices;

	if (FAILED(pD3dDevice->CreateBuffer(/*此处三个参数，参照指导书补齐，理解其含义*/)))
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
	pD3dDevice->IASetPrimitiveTopology(/*选择何种图元拓扑类型*/);
	pD3dDevice->IASetInputLayout(mVertexLayout);

	pD3dDevice->DrawIndexed(/*补齐三个参数并理解含义*/);
}

void Shape::buildVertexLayouts(ID3D10Device* pD3dDevice, ID3D10EffectTechnique*	pTech)
{
	// Create the vertex input layout.
	D3D10_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		/*补齐两个元素，理解*/
	};
	// Create the input layout
	D3D10_PASS_DESC PassDesc;
	pTech->GetPassByIndex(0)->GetDesc(&PassDesc);
	pD3dDevice->CreateInputLayout(vertexDesc, 2, PassDesc.pIAInputSignature,
		PassDesc.IAInputSignatureSize, &mVertexLayout);
}

