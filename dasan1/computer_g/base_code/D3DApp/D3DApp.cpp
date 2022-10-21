#include "D3DApp.h"


D3DApp::D3DApp(HINSTANCE hInstance)
{
	mhAppInst = hInstance;
}


D3DApp::~D3DApp(void)
{
}

void D3DApp::initApp()
{
	
	initMainWindow();
	initDirect3D();
	
}

void D3DApp::initMainWindow()
{
	WNDCLASS wc;

	TCHAR szTitle[] = TEXT("TESTDEMO");					// 标题栏文本
	TCHAR szWindowClass[] = TEXT("WCLASS");	


	//wcex.cbSize = sizeof(WNDCLASSEX);

	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc	=  WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= mhAppInst;
	wc.hIcon			= LoadIcon(mhAppInst, MAKEINTRESOURCE(IDI_APPLICATION));
	wc.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName	= NULL;
	wc.lpszClassName	= szWindowClass;
	//wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	//RegisterClassEx(&wcex);
	if (!RegisterClass (&wc))
     {
		
		return  ;
     }

	int width = ::GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	mClientWidth = width/2;
	mClientHeight = height/2;

	mhMainWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		width/4, height/4, mClientWidth, mClientHeight, NULL, NULL, mhAppInst, NULL);
	
	
   if (!mhMainWnd)
   {
	   MessageBox (	NULL, TEXT ("This program requires Windows NT!"), 
          				TEXT(""), MB_ICONERROR) ;
      return;
   }

   ShowWindow(mhMainWnd, SW_SHOW);
   UpdateWindow(mhMainWnd);
}


//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//

//LRESULT CALLBACK WndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

 LRESULT  D3DApp::msgProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (msg)
	{
	case WM_KEYDOWN:
		if(wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
		return 1;
	case WM_ACTIVATE:
		if(LOWORD(wParam) == WA_INACTIVE)
		{
			mAppPaused = true;
		}
		else
		{
			mAppPaused = false;
		}
		return 1;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 1;
	
	}
	return 0;
}

void D3DApp::initDirect3D()
{
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd,sizeof(sd));
	RECT rect;
	GetClientRect(mhMainWnd,&rect);
	sd.BufferDesc.Width = rect.right-rect.left;// mClientWidth;
	sd.BufferDesc.Height = rect.bottom-rect.top;//mClientHeight;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = mhMainWnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;



	D3D10CreateDeviceAndSwapChain(0,D3D10_DRIVER_TYPE_HARDWARE,0,0,
		D3D10_SDK_VERSION,&sd,&mSwapChain,&md3dDevice);


	ID3D10Texture2D* backBuffer;
	mSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D),  reinterpret_cast<void**>(&backBuffer)); 
	md3dDevice->CreateRenderTargetView(backBuffer, 0, &mRenderTargetView); 
	  
	D3D10_TEXTURE2D_DESC depthStencilDesc; 
	depthStencilDesc.Width = mClientWidth;
	depthStencilDesc.Height = mClientHeight; 
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize= 1; 
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count   = 1; // multisampling must match
	depthStencilDesc.SampleDesc.Quality = 0; // swap chain values. 
	depthStencilDesc.Usage = D3D10_USAGE_DEFAULT; 
	depthStencilDesc.BindFlags = D3D10_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0; 
	depthStencilDesc.MiscFlags = 0;  

	md3dDevice->CreateTexture2D( &depthStencilDesc, 0, &mDepthStencilBuffer);
	md3dDevice->CreateDepthStencilView( mDepthStencilBuffer, 0, &mDepthStencilView);  
	md3dDevice->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView); 
	D3D10_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width    = mClientWidth;
	vp.Height   = mClientHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;  
    md3dDevice->RSSetViewports(1, &vp); 

	D3DX10_FONT_DESC fontDesc;
	fontDesc.Height		=	24;
	fontDesc.Width		=	0;
	fontDesc.Weight		=	0;
	fontDesc.MipLevels	=	1;
	fontDesc.Italic		=	false;
	fontDesc.CharSet	=	DEFAULT_CHARSET;
	fontDesc.OutputPrecision	=	OUT_DEFAULT_PRECIS;
	fontDesc.Quality	=	DEFAULT_QUALITY;
	fontDesc.PitchAndFamily	=	DEFAULT_PITCH|FF_DONTCARE;
	wcscpy(fontDesc.FaceName,L"Times New Roman");

	D3DX10CreateFontIndirect(md3dDevice,&fontDesc,&mFont);
}

void D3DApp::onResize()
{
}

void D3DApp::drawScene()
{


	md3dDevice->ClearRenderTargetView(mRenderTargetView,mClearColor);

	md3dDevice->ClearDepthStencilView(mDepthStencilView,D3D10_CLEAR_DEPTH|D3D10_CLEAR_STENCIL,1.0f,0);
}

void D3DApp::updateScene(float dt)
{
	static int frameCnt = 0;
	static float t_base = 0.0f;

	frameCnt++;

	if((mTimer.getGameTime() - t_base)>1.0f)
	{
		float fps = (float)frameCnt;
		float mspf = 1000.0f/fps;

		std::wostringstream outs;
		outs.precision(6);

		outs<<L"FPS:"<<fps<<L"\n"<<"Milliseconds:Per Frame:"<<mspf;

		mFrameStats = outs.str();

		frameCnt = 0;
		t_base += 1.0f;
	}
}

int D3DApp::run()
{
	MSG msg = {0};

	mTimer.reset();

	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			mTimer.tick();

			if(!mAppPaused)
			{
				updateScene(mTimer.getDeltaTime());
			}else
			{
				Sleep(50);
			}
			drawScene();
		}
	}
	return (int)msg.wParam;
}