#include <Windows.h>

#define WINDOW_WIDTH 820
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE L"实验4"

// 全局变量声明部分

// 全局函数声明部分
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL Game_Init(HWND hwnd);
VOID Game_Paint(HWND hwnd);



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
        WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME,//
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
HDC hdc;//
PAINTSTRUCT ps;//

POINT lpPt1[6] = { 300, 10, 395, 79, 359, 191, 241, 191, 205, 79, 300, 10 };//
POINT lpPt2[6] = { 550, 10, 645, 79, 609, 191, 491, 191, 455, 79, 550, 10 };//

HBRUSH hBrush, hOldBrush;//
HPEN hPen, hOldPen;//

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{



    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);//
        Game_Paint(hwnd);//
        EndPaint(hwnd, &ps);//
        return 0;

    case WM_KEYDOWN:
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

BOOL Game_Init(HWND hwnd)
{
    hdc = GetDC(hwnd);
    Game_Paint(hwnd);
    ReleaseDC(hwnd, hdc);
    return TRUE;
}

VOID Game_Paint(HWND hwnd)
{
    int Round = 15; // 圆角角度

    // 左边绿色框
    hBrush = CreateSolidBrush(RGB(19, 197, 123));//
    hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);//
    hPen = CreatePen(PS_SOLID, 4, RGB(19 + 30, 197 + 30, 123 + 30));//
    hOldPen = (HPEN)SelectObject(hdc, hPen);//
    RoundRect(hdc, 10, 10, 180, 560, Round, Round);//

    // 左边俩小框
    hPen = CreatePen(PS_SOLID, 2, RGB(171 + 30, 93 + 30, 93 + 30));//
    hOldPen = (HPEN)SelectObject(hdc, hPen);//
    hBrush = CreateSolidBrush(RGB(171, 93, 93));//
    hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);//
    RoundRect(hdc, 40, 400, 140 + 10, 400 + 30, Round, Round);//
    // 左边俩小框
    hBrush = CreateSolidBrush(RGB(171, 93, 93));//
    hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);//
    RoundRect(hdc, 40, 400 + 50, 140 + 10, 400 + 80, Round, Round);//

    // 右边红色框
    hBrush = CreateSolidBrush(RGB(221, 82, 82));//
    hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);//
    hPen = CreatePen(PS_SOLID, 4, RGB(221 + 30, 82 + 30, 82 + 30));//
    hOldPen = (HPEN)SelectObject(hdc, hPen);//
    RoundRect(hdc, 185, 10, 185 + 600, 560, Round, Round);//

    // 右边线条
    hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//
    hOldPen = (HPEN)SelectObject(hdc, hPen);//
    for (int x = 185 + 50; x < (185 + 600); x += 50)//
    {
        MoveToEx(hdc, x, 10, NULL);//
        LineTo(hdc, x, 560);//
    }
    for (int y = 10 + 50; y < 560; y += 50)//
    {
        MoveToEx(hdc, 185, y, NULL);//
        LineTo(hdc, 185 + 600, y);//
    }

    SelectObject(hdc, hOldBrush);//
    SelectObject(hdc, hOldPen);//
    DeleteObject(hBrush);//
    DeleteObject(hOldPen);//
}