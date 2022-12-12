// LuaGameHost.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "LuaGameHost.h"
#include "lua.hpp"
#include "wrapddraw.h"
#include "wrapdinput.h"
#include "wrapTimer.h"
#include "wrapLua.h"
#include "wrapDMusic.h"
#include "wrapDSound.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE g_hInstance;								// 当前实例
HWND g_hMainWindow;

int nWindowWidth = 800;
int nWindowHeight = 600;
int nBPP = 16;
bool g_bWindowed = TRUE;

BOOL bActive = TRUE;		//应用程序是否活跃
//int		speed=12;			//延时速度
//int		fps;				//帧频率

TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void AdjustWindow(HWND hWnd, DWORD dwStyle,int clientWidth,int clientHeight);
int Game_ToggleScreenMode(void);
int Game_LoadImages();

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	Lua_Init();

	Lua_RegisterDInputKeyboardMapping();
	//Lua_RegisterDInputMouseButtonMapping();

	if ( Lua_DoFile ( TEXT("LuaGameHost.lua" )) )
	{
		MessageBox(g_hMainWindow,TEXT("LuaGameHost.lua 脚本运行错误!"),TEXT("错误"),MB_ICONSTOP | MB_OK);
		return 0;
	}

	nWindowWidth  = Lua_ReadGlobalNumber("WINDOW_WIDTH");
	nWindowHeight = Lua_ReadGlobalNumber("WINDOW_HEIGHT");
	nBPP		  = Lua_ReadGlobalNumber("BPP");
	g_bWindowed   = !Lua_ReadGlobalBoolean("FULLSCREEN");
	Lua_ReadGlobalString("GAME_TITLE",szTitle);

	// 初始化全局字符串
	LoadString(hInstance, IDC_LUAGAMEHOST, szWindowClass, MAX_LOADSTRING);

	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}


	DDraw_Init();

	DInput_Init();
	DMusic_Init();
	DSound_Init();
	Timer_Init();

	g_bWindowed = !g_bWindowed;
	Game_ToggleScreenMode();

	if(0 != Lua_CallFunction("Initialize"))
	{
		MessageBox(g_hMainWindow,TEXT("运行脚本函数 Initialize 时发生错误!"),TEXT("错误"),MB_ICONSTOP | MB_OK);
		msg.wParam = 1;
		goto QUIT;
		//return 0;
	}


	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LUAGAMEHOST));

	//// 主消息循环:
	//while (GetMessage(&msg, NULL, 0, 0))
	//{
	//	if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
	//	{
	//		TranslateMessage(&msg);
	//		DispatchMessage(&msg);
	//	}
	//}

	while(TRUE)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if(!GetMessage(&msg, NULL, 0, 0 )) 
				break;

			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		}
		else if(bActive)  //程序激活
		{
			DInput_GetKeyboardState ();		
			DInput_GetMouseState();
			Timer_HandleTimers ();						
			
			msg.wParam = Lua_CallFunction("HandleFrame");
			if(0 != msg.wParam)
			{
				break;
			}
		}
		//等待消息
		else 
			WaitMessage();
	}

	Lua_CallFunction ( "Terminate");

QUIT:

	DSound_DeleteAllSounds();
	DMusic_DeleteAllMIDI();
	DDraw_DeleteAllImage();

	DSound_Shutdown();
	DMusic_Shutdown();
	DInput_Shutdown();

	DDraw_FreeSurfaces();
	DDraw_Shutdown();

	Lua_ShutDown();
	
	return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释:
//
//    仅当希望
//    此代码与添加到 Windows 95 中的“RegisterClassEx”
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
//    这样应用程序就可以获得关联的
//    “格式正确的”小图标。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LUAGAMEHOST));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_LUAGAMEHOST);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   g_hInstance = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

  // ShowWindow(hWnd, nCmdShow);
  // UpdateWindow(hWnd);

   g_hMainWindow = hWnd;

   return TRUE;
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_ACTIVATEAPP://
		bActive = wParam;
		if( bActive )
		{
			DInput_SetAcquire(TRUE);
		}
		else
		{
			DInput_SetAcquire(FALSE);
		}

		break;

	case WM_SETCURSOR:
		if(LOWORD(lParam)!=HTCLIENT )
		{
			SetCursor(LoadCursor(NULL, IDC_ARROW));
		}
		else
		{
			SetCursor(NULL); 
		}
	break;

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}










int Game_ToggleScreenMode(void)
	{
		DWORD dwStyle;
		DDraw_FreeSurfaces();
		g_bWindowed = ! g_bWindowed;

		// In case we're coming from a fullscreen mode, restore the window size
		if (g_bWindowed)
		{
			dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
			SetMenu(g_hMainWindow,LoadMenu(g_hInstance,MAKEINTRESOURCE(IDC_LUAGAMEHOST)));
		}
		else
		{
			dwStyle =WS_POPUP;
			SetMenu(g_hMainWindow,NULL);
		}

		SetWindowLong(g_hMainWindow,GWL_STYLE,dwStyle);

		// Re-create the surfaces
		DDraw_InitSurfaces(nWindowWidth,nWindowHeight,nBPP);
		Game_LoadImages();
				

		if(g_bWindowed)
		{
			AdjustWindow(g_hMainWindow, dwStyle,nWindowWidth,nWindowHeight);
		}

		return 1;
	}

int Game_LoadImages()
{
	DDraw_DeleteAllImage();

	if (0 != Lua_CallFunction("LoadImages"))
	{
		return 0;
	}

	return 1;
}

	//将窗口客户区为指定大小,并居中显示
	void AdjustWindow(HWND hWnd, DWORD dwStyle,int clientWidth,int clientHeight)
	{
		RECT rect;
		//取得去掉windows系统菜单栏后的工作区
		RECT rcArea;
		SystemParametersInfo( SPI_GETWORKAREA, NULL, &rcArea, NULL );
		//取得客户区大小为640*480 对应的窗口大小
		RECT r;
		r.left=r.top=0;
		r.right=clientWidth;
		r.bottom=clientHeight;
		AdjustWindowRectEx( &r, dwStyle, TRUE, 0);

		// 将视窗的位置设定在屏幕（工作范围）的中央
		int w,h;
		w = r.right-r.left;
		h = r.bottom-r.top;

		rect.left = rcArea.left + ( rcArea.right-rcArea.left - w ) / 2;
		rect.top = rcArea.top + ( rcArea.bottom-rcArea.top - h ) / 2;
		rect.right = rect.left + w;
		rect.bottom = rect.top + h;

		SetWindowPos(hWnd, HWND_NOTOPMOST, rect.left, rect.top,
			(rect.right - rect.left), 
			(rect.bottom - rect.top), SWP_SHOWWINDOW );


	}



