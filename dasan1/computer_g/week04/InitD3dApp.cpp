#include "InitD3dApp.h"



InitD3DApp::InitD3DApp(HINSTANCE hInstance):D3DApp(hInstance)
{
	mClearColor = D3DXCOLOR(0.1f, 0.13f, 0.2f, 1.0f);
}


InitD3DApp::~InitD3DApp()
{
	if (md3dDevice)
		md3dDevice->ClearState();
}

void InitD3DApp::drawScene()
{
	D3DApp::drawScene();

	mSwapChain->Present(0,0);
}
