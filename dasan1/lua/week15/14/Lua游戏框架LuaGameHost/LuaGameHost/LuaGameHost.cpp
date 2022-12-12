// LuaGameHost.cpp : ����Ӧ�ó������ڵ㡣
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

// ȫ�ֱ���:
HINSTANCE g_hInstance;								// ��ǰʵ��
HWND g_hMainWindow;

int nWindowWidth = 800;
int nWindowHeight = 600;
int nBPP = 16;
bool g_bWindowed = TRUE;

BOOL bActive = TRUE;		//Ӧ�ó����Ƿ��Ծ
//int		speed=12;			//��ʱ�ٶ�
//int		fps;				//֡Ƶ��

TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������:
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

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	Lua_Init();

	Lua_RegisterDInputKeyboardMapping();
	//Lua_RegisterDInputMouseButtonMapping();

	if ( Lua_DoFile ( TEXT("LuaGameHost.lua" )) )
	{
		MessageBox(g_hMainWindow,TEXT("LuaGameHost.lua �ű����д���!"),TEXT("����"),MB_ICONSTOP | MB_OK);
		return 0;
	}

	nWindowWidth  = Lua_ReadGlobalNumber("WINDOW_WIDTH");
	nWindowHeight = Lua_ReadGlobalNumber("WINDOW_HEIGHT");
	nBPP		  = Lua_ReadGlobalNumber("BPP");
	g_bWindowed   = !Lua_ReadGlobalBoolean("FULLSCREEN");
	Lua_ReadGlobalString("GAME_TITLE",szTitle);

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDC_LUAGAMEHOST, szWindowClass, MAX_LOADSTRING);

	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
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
		MessageBox(g_hMainWindow,TEXT("���нű����� Initialize ʱ��������!"),TEXT("����"),MB_ICONSTOP | MB_OK);
		msg.wParam = 1;
		goto QUIT;
		//return 0;
	}


	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LUAGAMEHOST));

	//// ����Ϣѭ��:
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
		else if(bActive)  //���򼤻�
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
		//�ȴ���Ϣ
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
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
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   g_hInstance = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
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
		// �����˵�ѡ��:
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
		// TODO: �ڴ���������ͼ����...
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

// �����ڡ������Ϣ�������
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

	//�����ڿͻ���Ϊָ����С,��������ʾ
	void AdjustWindow(HWND hWnd, DWORD dwStyle,int clientWidth,int clientHeight)
	{
		RECT rect;
		//ȡ��ȥ��windowsϵͳ�˵�����Ĺ�����
		RECT rcArea;
		SystemParametersInfo( SPI_GETWORKAREA, NULL, &rcArea, NULL );
		//ȡ�ÿͻ�����СΪ640*480 ��Ӧ�Ĵ��ڴ�С
		RECT r;
		r.left=r.top=0;
		r.right=clientWidth;
		r.bottom=clientHeight;
		AdjustWindowRectEx( &r, dwStyle, TRUE, 0);

		// ���Ӵ���λ���趨����Ļ��������Χ��������
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



