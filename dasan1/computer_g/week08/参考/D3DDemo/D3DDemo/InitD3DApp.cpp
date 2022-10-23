#include "../../D3DApp/D3DApp.h"
#include "TriPyramid.h"
#include "LightTriPyramid.h"
#include "light.h"
#include "Box.h"

class InitD3DApp:public D3DApp
{
public:
	InitD3DApp(HINSTANCE hInstance);
	~InitD3DApp();

	void initApp();
	void onResize();
	void updateScene(float dt);
	void drawScene();

private:
	void buildFX();
	void buildVertexLayouts();

	Light mLights[3];
	int mLightType; //0 (parallel), 1 (point), 2 (spot)
	ShapeClass *pTriPyramid;
	ShapeClass *pLightTriPyramid;
	ShapeClass *pBox;

	ID3D10Effect* mFX;
	ID3D10EffectTechnique*  mTech;
	ID3D10InputLayout*	mVertexLayout;

	ID3D10Effect* mFXLight;
	ID3D10EffectTechnique*  mTechLight;
	ID3D10InputLayout*	mVertexLayoutLight;

	ID3D10Effect* mFXTex;
	ID3D10EffectTechnique*  mTechTex;
	ID3D10InputLayout*	mVertexLayoutTex;

	ID3D10ShaderResourceView* mDiffuseMapRV;
	ID3D10ShaderResourceView* mSpecMapRV;

	ID3D10EffectShaderResourceVariable* mfxDiffuseMapVar;
	ID3D10EffectShaderResourceVariable* mfxSpecMapVar;
	ID3D10EffectMatrixVariable* mfxTexMtxVar;

	ID3D10EffectMatrixVariable*  mfxWVPVarForTex;
	ID3D10EffectVariable* mfxLightVarForTex;
	ID3D10EffectMatrixVariable* mfxWorldVarForTex;
	ID3D10EffectVariable* mfxEyePosVarForTex;

	ID3D10EffectMatrixVariable*  mfxWVPVar;

	ID3D10EffectMatrixVariable*  mfxWVPVarForLight;
	ID3D10EffectMatrixVariable* mfxWorldVar;
	ID3D10EffectVariable* mfxEyePosVar;
	ID3D10EffectVariable* mfxLightVar;
	ID3D10EffectScalarVariable* mfxLightType;

	D3DXMATRIX	mView;
	D3DXMATRIX	mProj;
	D3DXMATRIX  mWorld;
	D3DXMATRIX	mWVP;

	D3DXVECTOR3 mEyePos;

	float mTheta;
	float mPhi;
};

InitD3DApp::InitD3DApp(HINSTANCE hInstance):D3DApp(hInstance)
{
	D3DXMatrixIdentity(&mView);
	D3DXMatrixIdentity(&mProj);
	D3DXMatrixIdentity(&mWorld);
	D3DXMatrixIdentity(&mWVP);


}

InitD3DApp::~InitD3DApp()
{
	if(md3dDevice)
		md3dDevice->ClearState();
}

void InitD3DApp::initApp()
{
	D3DApp::initApp();

	float aspect = (float)mClientWidth/mClientHeight;
	D3DXMatrixPerspectiveFovLH(&mProj, 0.25f*3.14f, aspect, 1.0f, 1000.0f);

	pTriPyramid = new TriPyramid(md3dDevice);
	pTriPyramid->Initialize();
	pTriPyramid->Move(D3DXVECTOR3(-2.0f,0.0f,0.0f));

	pLightTriPyramid = new LightTriPyramid(md3dDevice);
	pLightTriPyramid->Initialize();
	pLightTriPyramid->Move(D3DXVECTOR3(2.0f,0.0f,0.0f));

	pBox = new Box(md3dDevice);
	pBox->Initialize();
	pBox->Zoom(0.7f);
	

	if(FAILED(D3DX10CreateShaderResourceViewFromFile(md3dDevice,L"WoodCrate01.dds",0,0,&mDiffuseMapRV,0)))
	{
		MessageBox(0,L"文件加载失败", 0, 0);
	}

	if(FAILED(D3DX10CreateShaderResourceViewFromFile(md3dDevice,L"defaultspec.dds",0,0,&mSpecMapRV,0)))
	{
		MessageBox(0,L"文件加载失败", 0, 0);
	}

	mPhi = 0.0f;
	mTheta = 0.0f;

	buildFX();
	buildVertexLayouts();

	mLightType = 0;

	// Parallel light.
	mLights[0].dir      = D3DXVECTOR3(0.57735f, -0.57735f, 0.57735f);
	mLights[0].ambient  = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
	mLights[0].diffuse  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	mLights[0].specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
 
	// Pointlight--position is changed every frame to animate.
	mLights[1].ambient  = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
	mLights[1].diffuse  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	mLights[1].specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	mLights[1].att.x    = 0.0f;
	mLights[1].att.y    = 0.1f;
	mLights[1].att.z    = 0.0f;
	mLights[1].range    = 50.0f;

	// Spotlight--position and direction changed every frame to animate.
	mLights[2].ambient  = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
	mLights[2].diffuse  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	mLights[2].specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	mLights[2].att.x    = 1.0f;
	mLights[2].att.y    = 0.0f;
	mLights[2].att.z    = 0.0f;
	mLights[2].spotPow  = 64.0f;
	mLights[2].range    = 10000.0f;
}

void InitD3DApp::onResize()
{
	D3DApp::onResize();
}

void InitD3DApp::updateScene(float dt)
{
	D3DApp::updateScene(dt);

	//通过键盘控制摄像机的角度
	if(GetAsyncKeyState('A') & 0x8000)	mTheta -= 2.0f*dt;
	if(GetAsyncKeyState('D') & 0x8000)	mTheta += 2.0f*dt;
	if(GetAsyncKeyState('W') & 0x8000)	mPhi -= 2.0f*dt;
	if(GetAsyncKeyState('S') & 0x8000)	mPhi += 2.0f*dt;

	if( mPhi < 0.1f )	mPhi = 0.1f;
	if( mPhi > 3.14f-0.1f)	mPhi = 3.14f-0.1f;

	//if( mTheta < 0.1f )	mTheta = 0.1f;
	//if( mTheta > 3.14f-0.1f)	mTheta = 3.14f-0.1f;

	//计算摄像机的位置
	mEyePos.x =  5.0f*sinf(mPhi)*sinf(mTheta);
	mEyePos.z = -5.0f*sinf(mPhi)*cosf(mTheta);
	mEyePos.y =  5.0f*cosf(mPhi);

	//得到观察矩阵

	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&mView, &mEyePos, &target, &up);

	if(GetAsyncKeyState('1') & 0x8000)	mLightType = 0;
	if(GetAsyncKeyState('2') & 0x8000)	mLightType = 1;
	if(GetAsyncKeyState('3') & 0x8000)	mLightType = 2;

	
}

void InitD3DApp::drawScene()
{
	D3DApp::drawScene();
	RECT r = {5,5,0,0};
	mFont->DrawText(0,mFrameStats.c_str(),-1,&r,DT_NOCLIP,D3DXCOLOR(1.0,1.0,1.0,1.0));
	
	md3dDevice->OMSetDepthStencilState(0,0);
	float blendFactors[] = {0.0f, 0.0f, 0.0f, 0.0f};
	md3dDevice->OMSetBlendState(0, blendFactors, 0xffffffff);
    
    md3dDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	md3dDevice->IASetInputLayout(mVertexLayout);
	
	D3D10_TECHNIQUE_DESC techDesc;
    mTech->GetDesc( &techDesc );
    for(UINT p = 0; p < techDesc.Passes; ++p)
    {
		mWorld = pTriPyramid->GetWorldMatrix();
		mWVP = mWorld*mView*mProj;
		mfxWVPVar->SetMatrix((float*)&mWVP);

        mTech->GetPassByIndex( p )->Apply(0);
        
		pTriPyramid->Render();
    }

	md3dDevice->IASetInputLayout(mVertexLayoutLight);
	mfxEyePosVar->SetRawValue(&mEyePos, 0, sizeof(D3DXVECTOR3));
	mfxLightVar->SetRawValue(&mLights[mLightType], 0, sizeof(Light));
	mfxLightType->SetInt(mLightType);

	D3D10_TECHNIQUE_DESC techDesc2;
    mTechLight->GetDesc( &techDesc2 );
    for(UINT p = 0; p < techDesc2.Passes; ++p)
    {

		mWorld = pLightTriPyramid->GetWorldMatrix();
		mWVP = mWorld*mView*mProj;
		mfxWVPVarForLight->SetMatrix((float*)&mWVP);
		mfxWorldVar->SetMatrix((float*)&mWorld);
        mTechLight->GetPassByIndex( p )->Apply(0);
        
		pLightTriPyramid->Render();
    }

	md3dDevice->IASetInputLayout(mVertexLayoutTex);
	//mEyePos = D3DXVECTOR3(0,0,-5);
	mfxEyePosVarForTex->SetRawValue(&mEyePos, 0, sizeof(D3DXVECTOR3));
	mfxLightVarForTex->SetRawValue(&mLights[mLightType], 0, sizeof(Light));
	

	D3D10_TECHNIQUE_DESC techDesc3;
    mTechTex->GetDesc( &techDesc3 );
    for(UINT p = 0; p < techDesc3.Passes; ++p)
    {

		mWorld = pBox->GetWorldMatrix();
		mWVP = mWorld*mView*mProj;
		mfxWVPVarForTex->SetMatrix((float*)&mWVP);
		mfxWorldVarForTex->SetMatrix((float*)&mWorld);
		mfxDiffuseMapVar->SetResource(mDiffuseMapRV);
		mfxSpecMapVar->SetResource(mSpecMapRV);

		D3DXMATRIX texMat;
		D3DXMatrixIdentity(&texMat);
		mfxTexMtxVar->SetMatrix((float*)&texMat);

        mTechTex->GetPassByIndex( p )->Apply(0);
        
		pBox->Render();
    }

	mSwapChain->Present(0,0);
}

InitD3DApp *pApp;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE prevInstance,PSTR cmdLine,int showCmd)
{
	pApp = new InitD3DApp(hInstance);

	pApp->initApp();

	return pApp->run();
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	if(pApp->msgProc(message,wParam,lParam) == 0)
		return DefWindowProc(hwnd,message,wParam,lParam);
	return 0;
}

void InitD3DApp::buildFX()
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
	if(FAILED(hr))
	{
		if( compilationErrors )
		{
			MessageBoxA(0, (char*)compilationErrors->GetBufferPointer(), 0, 0);
		
		}
	} 

	mTech = mFX->GetTechniqueByName("ColorTech");
	
	hr = D3DX10CreateEffectFromFile(L"lighting.fx", 0, 0, 
		"fx_4_0", shaderFlags, 0, md3dDevice, 0, 0, &mFXLight, &compilationErrors, 0);
	if(FAILED(hr))
	{
		if( compilationErrors )
		{
			MessageBoxA(0, (char*)compilationErrors->GetBufferPointer(), 0, 0);
		
		}
	} 

	mTechLight = mFXLight->GetTechniqueByName("LightTech");

	hr = D3DX10CreateEffectFromFile(L"tex.fx", 0, 0, 
		"fx_4_0", shaderFlags, 0, md3dDevice, 0, 0, &mFXTex, &compilationErrors, 0);
	if(FAILED(hr))
	{
		if( compilationErrors )
		{
			MessageBoxA(0, (char*)compilationErrors->GetBufferPointer(), 0, 0);
		
		}
	} 

	mTechTex = mFXTex->GetTechniqueByName("TexTech");

	mfxWVPVarForTex = mFXTex->GetVariableByName("gWVP")->AsMatrix();
	mfxWorldVarForTex = mFXTex->GetVariableByName("gWorld")->AsMatrix();
	mfxEyePosVarForTex = mFXTex->GetVariableByName("gEyePosW");
	mfxLightVarForTex  = mFXTex->GetVariableByName("gLight");
	mfxDiffuseMapVar = mFXTex->GetVariableByName("gDiffuseMap")->AsShaderResource();
	mfxSpecMapVar    = mFXTex->GetVariableByName("gSpecMap")->AsShaderResource();
	mfxTexMtxVar     = mFXTex->GetVariableByName("gTexMtx")->AsMatrix();

	mfxWVPVar = mFX->GetVariableByName("gWVP")->AsMatrix();
	mfxWVPVarForLight = mFXLight->GetVariableByName("gWVP")->AsMatrix();
	mfxWorldVar = mFXLight->GetVariableByName("gWorld")->AsMatrix();
	mfxEyePosVar = mFXLight->GetVariableByName("gEyePosW");
	mfxLightVar  = mFXLight->GetVariableByName("gLight");
	mfxLightType = mFXLight->GetVariableByName("gLightType")->AsScalar();
}

void InitD3DApp::buildVertexLayouts()
{
	// Create the vertex input layout.
	D3D10_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0}
	};

	// Create the input layout
    D3D10_PASS_DESC PassDesc;
    mTech->GetPassByIndex(0)->GetDesc(&PassDesc);
    md3dDevice->CreateInputLayout(vertexDesc, 2, PassDesc.pIAInputSignature,
		PassDesc.IAInputSignatureSize, &mVertexLayout);

	// Create the vertex input layout.
	D3D10_INPUT_ELEMENT_DESC vertexDesc2[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"DIFFUSE",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"SPECULAR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 40, D3D10_INPUT_PER_VERTEX_DATA, 0}	};

	// Create the input layout
    D3D10_PASS_DESC PassDesc2;
    mTechLight->GetPassByIndex(0)->GetDesc(&PassDesc2);
    md3dDevice->CreateInputLayout(vertexDesc2, 4, PassDesc2.pIAInputSignature,
		PassDesc2.IAInputSignatureSize, &mVertexLayoutLight);

	// Create the vertex input layout.
	D3D10_INPUT_ELEMENT_DESC vertexDesc3[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0}	};

	// Create the input layout
    D3D10_PASS_DESC PassDesc3;
    mTechTex->GetPassByIndex(0)->GetDesc(&PassDesc3);
    md3dDevice->CreateInputLayout(vertexDesc3, 3, PassDesc3.pIAInputSignature,
		PassDesc3.IAInputSignatureSize, &mVertexLayoutTex);
}