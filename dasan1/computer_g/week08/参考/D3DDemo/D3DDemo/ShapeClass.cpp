#include "ShapeClass.h"


ShapeClass::ShapeClass(ID3D10Device* device)
{
	mD3DDevice = device;
	mVertexCount = 0;
	mIndexCount = 0;
	mVertexBuffer = 0;
	mIndexBuffer = 0;

	pos = D3DXVECTOR3(0,0,0);
	angle = D3DXVECTOR3(0,0,0);
	scale = 1.0f;

	D3DXMatrixIdentity(&worldMat);
	D3DXMatrixIdentity(&tranMat);
	D3DXMatrixIdentity(&rotXMat);
	D3DXMatrixIdentity(&rotYMat);
	D3DXMatrixIdentity(&rotZMat);
	D3DXMatrixIdentity(&zoomMat);

}


ShapeClass::~ShapeClass(void)
{
}


//bool ShapeClass::Initialize()
//{
//	return true;
//}
void ShapeClass::Shutdown()
{
	if(mIndexBuffer)
	{
		mIndexBuffer->Release();
		mIndexBuffer = 0;
	}
	if(mVertexBuffer)
	{
		mVertexBuffer->Release();
		mVertexBuffer = 0;
	}
}

void ShapeClass::Render()
{
	UINT stride = VertexSize;
	UINT offset = 0;
	mD3DDevice->IASetVertexBuffers(0,1,&mVertexBuffer,&stride,&offset);
	mD3DDevice->IASetIndexBuffer(mIndexBuffer,DXGI_FORMAT_R32_UINT,0);
	mD3DDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	mD3DDevice->DrawIndexed(mIndexCount,0,0);
}

int ShapeClass::GetIndexCount()
{
	return 0;
}

void ShapeClass::UpdateMatrix()
{
	D3DXMatrixTranslation(&tranMat,pos.x,pos.y,pos.z);
	D3DXMatrixRotationX(&rotXMat,angle.x);
	D3DXMatrixRotationY(&rotYMat,angle.y);
	D3DXMatrixRotationZ(&rotZMat,angle.z);
	D3DXMatrixScaling(&zoomMat,scale,scale,scale);

	worldMat = rotXMat*rotYMat*rotZMat*zoomMat*tranMat;
}

D3DXMATRIX ShapeClass::GetWorldMatrix()
{
	return worldMat;
}

void ShapeClass::Move(D3DXVECTOR3 d)
{
	pos += d;
	UpdateMatrix();
}

void ShapeClass::Rotate(D3DXVECTOR3 a)
{
	angle += a;
	UpdateMatrix();
}

void ShapeClass::Zoom(float s)
{
	scale *= s;
	UpdateMatrix();
}

void ShapeClass::ComputeNormal(const D3DXVECTOR3& p0,
	const D3DXVECTOR3& p1,
	const D3DXVECTOR3& p2,
	D3DXVECTOR3& out)
{
	D3DXVECTOR3 u = p1 - p0;
	D3DXVECTOR3 v = p2 - p0;
	D3DXVec3Cross(&out, &u, &v);
	D3DXVec3Normalize(&out, &out);
}
