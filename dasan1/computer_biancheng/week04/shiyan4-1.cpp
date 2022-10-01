#include <Windows.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE L"GDI程序核心框架"

// 全局变量声明部分

// 全局函数声明部分
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);



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
    HDC hdc;//
    PAINTSTRUCT ps;//

    POINT lpPt1[6] = { 300, 10, 395, 79, 359, 191, 241, 191, 205, 79, 300, 10 };//
    POINT lpPt2[6] = { 550, 10, 645, 79, 609, 191, 491, 191, 455, 79, 550, 10 };//

    HBRUSH hBrush, hOldBrush;//
    HPEN hPen, hOldPen;//

    switch (message)
    {
    case WM_PAINT:

        hdc = BeginPaint(hwnd, &ps);//
        

        //hBrush = (HBRUSH)GetStockObject(LTGRAY_BRUSH);//
        hBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 100, 100));//
        hPen = CreatePen(PS_DASHDOTDOT, 2, RGB(0, 0, 200));//

        hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);//
        hOldPen = (HPEN)SelectObject(hdc, hPen);//

        //for (int i = 50; i < 150; i++)//
        //    SetPixel(hdc, i, 100, RGB(0, 0, 0));//

        //MoveToEx(hdc, 100, 50, NULL);//
        //LineTo(hdc, 100, 150);//

        //Polyline(hdc, lpPt1, 5);//
        //Polygon(hdc, lpPt2, 6);//


        Rectangle(hdc, 40, 220, 230, 350);//
        //RoundRect(hdc, 40, 220, 230, 350, 30, 20);//

        //Ellipse(hdc, 40, 220, 40 + 30, 220 + 20);//

        Ellipse(hdc, 40 + 300, 220, 230 + 300, 350);//

        //Arc(hdc, 180, 220, 370, 350, 450, 285, 275, 200);//
        //Chord(hdc, 300, 220, 490, 350, 570, 285, 395, 200);//
        //Pie(hdc, 420, 220, 610, 350, 690, 285, 515, 200);//


        SelectObject(hdc, hOldBrush);//
        SelectObject(hdc, hOldPen);//

        DeleteObject(hBrush);//
        DeleteObject(hPen);//

        EndPaint(hwnd, &ps);//
        return 0;


        break;

    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
            DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

