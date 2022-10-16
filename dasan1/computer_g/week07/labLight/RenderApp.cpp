#include "RenderApp.h"



RenderApp::RenderApp(HINSTANCE hInstance) :D3DApp(hInstance)
{
	mClearColor = D3DXCOLOR(0.1f, 0.13f, 0.2f, 1.0f);
}


RenderApp::~RenderApp()
{
	if (md3dDevice)
		md3dDevice->ClearState();
}


void RenderApp::drawScene()
{
	D3DApp::drawScene();

	mWVP = mView * mProj;
	mfxWVPVar->SetMatrix((float*)&mWVP);

	D3D10_TECHNIQUE_DESC techDesc;
	mTech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		mTech->GetPassByIndex(p)->Apply(0);
		pTri->onFrameRender(md3dDevice);
	}

	mSwapChain->Present(0, 0);
}

void RenderApp::initApp()
{
	D3DApp::initApp();

	buildFX();

	pTri = new Shape();
	pTri->createTriangle(md3dDevice);
	pTri->buildVertexLayouts(md3dDevice, mTech);

	D3DXMatrixIdentity(&mView);
	D3DXMatrixIdentity(&mProj);
	D3DXMatrixIdentity(&mWVP);

	float aspect = (float)mClientWidth / mClientHeight;
	D3DXMatrixPerspectiveFovLH(&mProj, 0.25*3.14f, aspect, 1.0f, 100.0f);

	D3DXVECTOR3 pos(0, 0, -5);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&mView, &pos, &target, &up);
	

}

void RenderApp::buildFX()
{
	DWORD shaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

	ID3D10Blob* compilationErrors = 0;
	HRESULT hr = 0;
	hr = D3DX10CreateEffectFromFile(L"color.fx", 0, 0,
		"fx_4_0", shaderFlags, 0, md3dDevice, 0, 0, &mFX, &compilationErrors, 0);
	if (FAILED(hr))
	{
		if (compilationErrors)
		{
			MessageBoxA(0, (char*)compilationErrors->GetBufferPointer(), 0, 0);

		}
	}

	mTech = mFX->GetTechniqueByName("ColorTech");

	mfxWVPVar = mFX->GetVariableByName("gWVP")->AsMatrix();
}

