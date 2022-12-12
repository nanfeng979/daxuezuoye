#include "Game.h"

/*
	 CGame的构造函数
*/
CGame::CGame(int fps)
{
	nFps=fps;		//记录程序要求锁定的帧频
	if (fps > 0)	//如果要锁定的帧频大于0，则算出帧与帧之间的间隔时间
	{
		fFixedDeltaTime = 1000.0f / fps;
	}
	else			//否则，不限速，以系统最快速度运行
	{
		fFixedDeltaTime = 0;
	}
}
CGame::~CGame(void)						//在析构函数中释放资源
{
	if (pSpriteManager)
	{
		delete pSpriteManager;
	}
	if (pResManager)
	{
		delete pResManager;
	}
	if (hWnd && hdc)
	{
		ReleaseDC(hWnd,hdc);
	}
	if (hdcMem)
	{
		DeleteDC(hdcMem);
	}
	if (hbMem)
	{
		DeleteObject(hbMem);
	}


}

bool CGame::Run(HINSTANCE hInstance, int x, int y, int width, int height)
{
	static TCHAR szAppName[]=TEXT("Game");
	WNDCLASS wndclass;        //定义窗口类结构变量
	MSG msg;                  //定义消息结构变量

	/********定义窗口类各属性*******/
	wndclass.style=CS_HREDRAW|CS_VREDRAW;       //改变窗口大小则重画
	wndclass.lpfnWndProc=CGame::WndProc;               //窗口函数为  WndProc
	wndclass.cbClsExtra=0;                      //窗口类无扩展
	wndclass.cbWndExtra=0;                      //窗口实例无扩展
	wndclass.hInstance=hInstance;               //注册窗口类的实例句柄
	wndclass.hIcon=LoadIcon(NULL,IDI_APPLICATION); //窗口用默认图标
	wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);   //窗口用箭头光标
	wndclass.hbrBackground=NULL;//(HBRUSH)GetStockObject(WHITE_BRUSH); //背景为白色
	wndclass.lpszMenuName=NULL;                 //窗口默认无菜单
	wndclass.lpszClassName=szAppName;         

	if(!RegisterClass(&wndclass)) {
		MessageBox(NULL,TEXT("注册失败！"),szAppName,MB_ICONERROR);
		return false;
	}
	//创建窗口
	unsigned int nShow = SW_SHOW;					//窗口显示的样式默认为SW_SHOW
	unsigned int nWindowStyle = WS_OVERLAPPEDWINDOW;//窗口默认样式为重叠窗口样式
	if (x == 0)
	{
		x = CW_USEDEFAULT;
	}
	if (y == 0)
	{
		y = CW_USEDEFAULT;
	}
	if (width == 0)
	{
		width = 1200;
		nShow = SW_SHOWMAXIMIZED;
		nWindowStyle = WS_POPUP;
	}
	if (height == 0)
	{
		height = 800;
		nShow = SW_SHOWMAXIMIZED;
		nWindowStyle = WS_POPUP;
	}
	hWnd = CreateWindow(szAppName,//窗口类名
		szAppName,//窗口
		nWindowStyle,
		x,y,width,height,//系统缺省的坐标和宽度高度
		NULL,//窗口无父窗口
		NULL,//窗口无主菜单
		hInstance,//实例句柄
		NULL//无创建参数
		); 
	DWORD ret = GetLastError();
	ShowWindow(hWnd,nShow);              //显示窗口
	UpdateWindow(hWnd);                     //更新窗口的客户区
	SetProp(hWnd,TEXT("GameObj"),this);
	ReadyRenderContext();	//准备渲染环境，主要是创建双缓冲
	/*
		创建完窗口后，在进入消息循环之前，调用Init函数，完成特定游戏的初始化工作。
		由于Init函数式虚函数，在多态的作用下，此处会调用具体某个子类的Init函数来
		完成资源加载等初始化的工作。
	*/
	Init();	
	t0 = GetTickCount();//记录当前时刻点
	t = 0;
	nFrames = 0;
	nCalcFps = 0;
	msg.message   =   WM_NULL;   
	BOOL  bMessage;
	PeekMessage(&msg, NULL, 0, 0,PM_NOREMOVE);
	while(msg.message != WM_QUIT)	//进入消息循环
	{
		bMessage = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		if(bMessage)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if(IsKeyDown(VK_ESCAPE))
			DestroyWindow(hWnd);
		FrameFunc();												//消息循环中的没一帧，调用帧函数进行游戏更新
	} 
	RemoveProp(hWnd,TEXT("GameObj"));
	return true;
}
void CGame::ReadyRenderContext()
{
	hdc = GetDC(hWnd);	//得到设备环境
	
	GetClientRect(hWnd,&rectClient);								//得到客户区矩形
	//下面创建后备缓冲
	hdcMem = CreateCompatibleDC(hdc);
	hbMem = CreateCompatibleBitmap(hdc,rectClient.right-rectClient.left,rectClient.bottom-rectClient.top);
	SelectObject(hdcMem,hbMem);
	SetGraphicsMode(hdcMem, GM_ADVANCED);
	SetStretchBltMode(hdcMem, COLORONCOLOR);
	pResManager =  new CResourceManager(hWnd);						//创建资源管理对象
	pSpriteManager = new CSpriteManager(pResManager);				//创建精灵管理对象

}


/***************************************************************************
	帧函数，根据系统流逝的时间更新精灵状态，可以在子类重写游戏规则
***************************************************************************/
void CGame::FrameFunc()
{
	DWORD dt = 0;

	do 
	{ 
		dt=GetTickCount() - t0; 
	} while(dt < 1);									//保证最小间隔时间大于等于1毫秒
	if (dt >= fFixedDeltaTime)							//如果大于固定的间隔时间
	{
		t0 = GetTickCount();								//记录本帧调用的时刻
		Update(dt / 1000.0);							//调用帧函数更新
		t += dt / 1000.0;
		Render();										//渲染

		nFrames++;
	}
	else
	{
		Sleep(1);										//否则休眠1秒
	}
}
/***************************************************************************
	更新函数，通知SpriteManager对象管理的每个精灵更新自身
***************************************************************************/
void CGame::Update(float fDeltaTime)
{
	if (pSpriteManager)
	{
		pSpriteManager->Update(fDeltaTime);	
	}
}
/***************************************************************************
	渲染函数，通知SpriteManager对象管理的每个精灵渲染自身。
	每个精灵是将自身渲染到后备缓冲里的，当所有精灵对象都完成了自身的渲染后，
	该函数将后备缓冲的内容BitBlt到屏幕上，完成显示。
***************************************************************************/
void CGame::Render()
{
	FillRect(hdcMem,&rectClient,(HBRUSH)GetStockObject(BLACK_BRUSH));
	if (pSpriteManager)
	{
		pSpriteManager->Render(hdcMem);
	}
	if (t >= 1)
	{
		nCalcFps  =  nFrames / t;

		t = 0;
		nFrames = 0;
	}
	wsprintf(szBuf,TEXT("%d"),nCalcFps);
	TextOut(hdcMem,10,10,szBuf,wcslen(szBuf));

	BitBlt(hdc,0,0,rectClient.right - rectClient.left,rectClient.bottom - rectClient.top,hdcMem,0,0,SRCCOPY);
	
}
bool CGame::IsKeyDown(short vk_code)
{
	return (GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0;
}

bool CGame::IsKeyUp(int vk_code)
{
	static int keyBuf[256] = {0};
	short key = GetAsyncKeyState(vk_code); 
	int curKeyFlag = (key & 0x8000) ? 1:0;
	if (keyBuf[vk_code] == 1 && curKeyFlag == 0){
		keyBuf[vk_code] = 0;
		return true;
	}
	keyBuf[vk_code] = curKeyFlag;
	return 0;
}


//窗口函数
LRESULT CALLBACK CGame::WndProc(HWND hwnd,UINT message,WPARAM wParam, LPARAM lParam)
{
	CGame *pGame =(CGame*)GetProp(hwnd,TEXT("GameObj"));

	switch(message)                  //根据消息值转相应的消息处理
	{
	case  WM_DESTROY:                //撤消窗口消息
		PostQuitMessage(0);          //产生退出程序消息WM_QUIT
		return 0;
	case WM_LBUTTONDOWN:
		if (pGame)
			pGame->HandleLMouseDown(wParam,lParam);
		return 0;
	case WM_LBUTTONUP:
		if (pGame)
			pGame->HandleLMouseUp(wParam,lParam);
		return 0;
	case WM_LBUTTONDBLCLK:
		if (pGame)
			pGame->HandleLDoubleClick(wParam,lParam);
		return 0;
	case WM_MOUSEMOVE:
		if (pGame)
			pGame->HandleMouseMove(wParam,lParam);
		return 0;
	case WM_RBUTTONDOWN:
		if (pGame)
			pGame->HandleRMouseDown(wParam,lParam);
		return 0;
	case WM_RBUTTONUP:
		if (pGame)
			pGame->HandleRMouseUp(wParam,lParam);
		return 0;
	case WM_RBUTTONDBLCLK:
		if (pGame)
			pGame->HandleRDoubleClick(wParam,lParam);
		return 0;
	case WM_MBUTTONDOWN:
		if (pGame)
			pGame->HandleMMouseDown(wParam,lParam);
		return 0;
	case WM_MBUTTONUP:
		if (pGame)
			pGame->HandleMMouseUp(wParam,lParam);
		return 0;
	case WM_MBUTTONDBLCLK:
		if (pGame)
			pGame->HandleMDoubleClick(wParam,lParam);
		return 0;
	case WM_KEYDOWN:
		if (pGame)
			pGame->HandleKeyDown(wParam,lParam);
		return 0;
	case WM_KEYUP:
		if (pGame)
			pGame->HandleKeyUp(wParam,lParam);
		return 0;
	}
	return DefWindowProc(hwnd,message,wParam,lParam);//其它转默认窗口函数
}
