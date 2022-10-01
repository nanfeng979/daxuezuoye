#include <Windows.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE L"GDI程序核心框架"

// 全局变量声明部分
HDC g_hdc = NULL;

// 全局函数声明部分
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL Game_Init(HWND hwnd);
VOID Game_Paint(HWND hwnd);
//BOOL Game_CleanUp(HWND hwnd);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    WNDCLASS wndClass = { 0 };
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.lpszClassName = L"xiang";
    wndClass.lpszMenuName = NULL;

    if (!RegisterClass(&wndClass))
    {
        MessageBox(NULL, L"窗口类创建失败", L"wndClass created fail!", 0);
    }

    HWND hwnd = CreateWindow(
        L"xiang",
        WINDOW_TITLE,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL
        );

    if (!hwnd)
    {
        MessageBox(hwnd, L"窗口创建失败", L"window created fail!", 0);
        return 0;
    }

    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    if (!Game_Init(hwnd))
    {
        MessageBox(hwnd, L"资源初始化失败", L"消息窗口", 0);
        return FALSE;
    }

    MSG msg = { 0 };
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    UnregisterClass(L"窗口注销", wndClass.hInstance);
    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT paintStruct;

    switch (message)
    {
    case WM_PAINT:
        g_hdc = BeginPaint(hwnd, &paintStruct);
        Game_Paint(hwnd);
        EndPaint(hwnd, &paintStruct);
        ValidateRect(hwnd, NULL);
        break;

    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
            DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
        // Game_Cleanup(hwnd);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

BOOL Game_Init(HWND hwnd)
{
    g_hdc = GetDC(hwnd);
    Game_Paint(hwnd);
    ReleaseDC(hwnd, g_hdc);
    return TRUE;
}

VOID Game_Paint(HWND hwnd)
{

}

