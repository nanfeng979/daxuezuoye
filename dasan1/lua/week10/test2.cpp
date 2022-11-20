// test2.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "test2.h"

//extern   "C" {
//#include "lua.h"
//    /*Lua.h定义了Lua提供的基础函数,包括创建Lua环境、
//    调用Lua函数（如lua_pcall）、读写Lua环境中全局变量，
//    以及注册供Lua调用的新函数等。Lua.h定义所有内容都有一个Lua_前缀。*/
//#include "lauxlib.h"
//#include "lualib.h"
//    /*Lauxlib.h定义了辅助库提供函数。所有定义以luaL_开头。*/
//}
#include "lua.hpp"



#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

int pw;
int ph;

 
// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


void error(lua_State* L, const char* fmt, ...)
{
    va_list argp;
    //将字符串读入到参数列表
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    //参数列表清0
    va_end(argp);
    //关闭lua状态
    lua_close(L);
    system("pause");
    exit(EXIT_FAILURE);
}


void load(lua_State* L, const char* fname, int* w, int* h)
{
    //加载文件
    if (luaL_loadfile(L, fname) || lua_pcall(L, 0, 0, 0))
        error(L, "cannot run config. file: %s", lua_tostring(L, -1));
    //读取lua中的全局变量压入栈
    lua_getglobal(L, "width");
    lua_getglobal(L, "height");
    //检测栈中的元素是否是number类型
    if (!lua_isnumber(L, -2))
        error(L, "'width' should be a number\n");
    if (!lua_isnumber(L, -1))
        error(L, "'height' should be a number\n");
    //读取栈中的元素分别给变量w和h
    *w = lua_tointeger(L, -2);
    *h = lua_tointeger(L, -1);

}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。


    //lua_State* pluaState = lua_open();	//新建一个lua的虚拟栈
    lua_State* pluaState = luaL_newstate();
   luaL_openlibs(pluaState);

    /*******************************************************************************************/
    /**********    方法一：加载lua文件并获得文件中的值代码如下，也可以通过一个函数调用，如方法二   *****************************/
    if (luaL_loadfile(pluaState, "wh.lua") || lua_pcall(pluaState, 0, 0, 0))
        // luaL_loadfile函数返回值：返回1 表示有错误，返回0表示无错误
    {
        error(pluaState, "read invaild");

    }

    lua_getglobal(pluaState, "width");
    lua_getglobal(pluaState, "height");
    //检测栈中的元素是否是number类型
    if (!lua_isnumber(pluaState, -2))
        error(pluaState, "'width' should be a number\n");
    if (!lua_isnumber(pluaState, -1))
        error(pluaState, "'height' should be a number\n");
    //读取栈中的元素分别给变量pw和ph
    pw = lua_tointeger(pluaState, -2);
    ph = lua_tointeger(pluaState, -1);


    /**************************************************************************************/
     //方法二：调用函数加载lua文件，并获得文件中的值
      //load(pluaState,"wh.lua",&pw,&ph);
 /**************************************************************************************/
     
   /**************************************************************************************/
     //方法三：调用函数加载lua文件并执行，这里省略了错误处理
      //luaL_dofile(pluaState, "wh.lua");
      //lua_getglobal(pluaState, "width");
      //lua_getglobal(pluaState, "height");
      //pw = lua_tointeger(pluaState, -2);
      // ph = lua_tointeger(pluaState, -1); 
 /**************************************************************************************/


    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TEST2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEST2));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEST2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TEST2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, pw, ph, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
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
