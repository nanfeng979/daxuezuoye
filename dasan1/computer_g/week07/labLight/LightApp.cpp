#include "LightApp.h"




LightApp::LightApp(HINSTANCE hInstance) :D3DApp(hInstance)
{
	mClearColor = D3DXCOLOR(0.1f, 0.13f, 0.2f, 1.0f);
}


LightApp::~LightApp()
{
	if (md3dDevice)
		md3dDevice->ClearState();
}


void LightApp::drawScene()
{
	D3DApp::drawScene();

	::D3DXMATRIX mWorld;
	::D3DXMatrixIdentity(&mWorld);
	::D3DXMatrixRotationY(&mWorld, 0.5f);

	mfxLightTypeVar->SetInt(lightIndex);
	mWVP = mWorld* mView * mProj;
	mfxWorldVar->SetMatrix((float*)&mWorld);
	mfxWVPVar->SetMatrix((float*)&mWVP);
	mfxEyePosVar->SetRawValue(&mEyePos, 0, sizeof(D3DXVECTOR3));
	mfxLightVar->SetRawValue(&lights[lightIndex], 0, sizeof(Light));


	D3D10_TECHNIQUE_DESC techDesc;
	mTech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		mTech->GetPassByIndex(p)->Apply(0);
		pTriPyramid->onFrameRender(md3dDevice);
	}

	mSwapChain->Present(0, 0);
}

void LightApp::initApp()
{
	D3DApp::initApp();

	buildFX();
	lights[0].dir = D3DXVECTOR3(0.577f, -0.577f, 0.5767f);
	lights[0].ambient = D3DXCOLOR(0.1f, 0.1f, 0.10f, 1.0f);
	lights[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	lights[0].specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	lights[1].dir = D3DXVECTOR3(0.577f, -0.577f, 0.5767f);
	lights[1].ambient = D3DXCOLOR(0.1f, 0.1f, 0.0f, 1.0f);
	lights[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	lights[1].specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	lights[1].att.x = 0.0f;
	lights[1].att.y = 0.1f;
	lights[1].att.z = 0.0f;
	lights[1].range = 50.0f;

	lights[2].dir = D3DXVECTOR3(0.577f, -0.577f, 0.5767f);
	lights[2].ambient = D3DXCOLOR(0.1f, 0.0f, 0.20f, 1.0f);
	lights[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	lights[2].specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	lights[2].att.x = 1.0f;
	lights[2].att.y = 0.0f;
	lights[2].att.z = 0.0f;
	lights[2].spotPow = 64.0f;
	lights[2].range = 1050.0f;

	/*pTri = new Shape();
	pTri->createTriangle(md3dDevice);
	pTri->buildVertexLayouts(md3dDevice, mTech);*/
	
	pTriPyramid = new Shape();
	pTriPyramid->createTriPyramid(md3dDevice);
	pTriPyramid->buildVertexLayouts(md3dDevice, mTech);

	D3DXMatrixIdentity(&mView);
	D3DXMatrixIdentity(&mProj);
	D3DXMatrixIdentity(&mWVP);

	float aspect = (float)mClientWidth / mClientHeight;
	D3DXMatrixPerspectiveFovLH(&mProj, 0.25 * 3.14f, aspect, 1.0f, 100.0f);

	lightIndex = 0;

	mEyePos = D3DXVECTOR3(0, 0, -5);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&mView, &mEyePos, &target, &up);


}

void LightApp::buildFX()
{
	DWORD shaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

	ID3D10Blob* compilationErrors = 0;
	HRESULT hr = 0;
	hr = D3DX10CreateEffectFromFile(L"lighting.fx", 0, 0,
		"fx_4_0", shaderFlags, 0, md3dDevice, 0, 0, &mFX, &compilationErrors, 0);
	if (FAILED(hr))
	{
		if (compilationErrors)
		{
			MessageBoxA(0, (char*)compilationErrors->GetBufferPointer(), 0, 0);

		}
	}

	mTech = mFX->GetTechniqueByName("LightTech");

	mfxEyePosVar = mFX->GetVariableByName("gEyePosW");
	//mfxEyePosVar->SetRawValue(&mEyePos, 0, sizeof(D3DXVECTOR3));
	mfxLightVar = mFX->GetVariableByName("gLight");
	mfxLightTypeVar = mFX->GetVariableByName("gLightType")->AsScalar();

	mfxWVPVar = mFX->GetVariableByName("gWVP")->AsMatrix();
	mfxWorldVar = mFX->GetVariableByName("gWorld")->AsMatrix();
}

