#include <Windows.h>
#include <cmath>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
VOID PAINT(HWND hwnd, HDC hdc);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG Msg;
	WNDCLASS wndclass;
	TCHAR lpszTitle[] = L"余庆祥设计";

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszMenuName = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = L"xiang";

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, L"注册窗口失败", L"注册窗口失败", MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(L"xiang", lpszTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	if (!hwnd)
	{
		MessageBox(NULL, L"创建窗口失败", L"创建窗口失败", MB_ICONERROR);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = GetDC(hwnd); // 获取设备环境
		PAINT(hwnd, hdc); // 绘制
		ReleaseDC(hwnd, hdc); // 释放设备环境
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

VOID PAINT(HWND hwnd, HDC hdc)
{
	// sin曲线
	#define PI 3.14159265358979323846
	#define init_x 300 // 原点的x轴位置
	#define init_y 150 // 原点的y轴位置
	#define origin_width init_x // 原点的x轴宽度度
	#define origin_height 100 // 原点的y轴高度

	// 绘制x坐标轴
	for (int i = init_x - origin_width; i < init_x + origin_width; i++)
	{
		SetPixel(hdc, i, init_y, RGB(0, 0, 0));
	}
	// 绘制y坐标轴
	for (int i = init_y - origin_height; i < init_y + origin_height; i++)
	{
		SetPixel(hdc, init_x, i, RGB(0, 0, 0));
	}

	// 绘制sin曲线
	// 绘制x轴正方向的曲线
	for (int i = init_x, xita = 0; i < init_x + origin_width; i++, xita++)
	{
		xita %= 360;
		SetPixel(hdc, i, sin(xita * PI / 180) * origin_height + init_y, RGB(255, 0, 0));
	}
	// 绘制x轴反方向的曲线
	for (int i = init_x, xita = 0; i > init_x - origin_width; i--, xita--)
	{
		xita %= 360;
		SetPixel(hdc, i, sin(xita * PI / 180) * origin_height + init_y, RGB(255, 0, 0));
	}

	// 抛物线
	#define distance_y 200 // 两个对象之间y轴的间距
	#define parabola_init_x init_x // 原点的x轴位置
	#define parabola_init_y init_y + origin_height + distance_y // 原点的y轴位置
	#define parabola_origin_width parabola_init_x - 100 // 原点的x轴宽度度
	#define parabola_origin_height 150 // 原点的y轴高度

	int p = 250; // 确定一个焦点位置

	// 绘制x坐标轴
	for (int i = parabola_init_x - (parabola_origin_width); i < parabola_init_x + parabola_origin_width; i++)
	{
		SetPixel(hdc, i, parabola_init_y, RGB(0, 0, 0));
	}
	// 绘制y坐标轴
	for (int i = parabola_init_y - (parabola_origin_height); i < parabola_init_y + parabola_origin_height; i++)
	{
		SetPixel(hdc, parabola_init_x, i, RGB(0, 0, 0));
	}
	// 绘制抛物线
	for (int x = -(parabola_origin_width / 2), y = 0; x < (parabola_origin_width / 2); x++)
	{
		y = x * x / (2 * p);
		SetPixel(hdc, x + parabola_init_x, parabola_init_y - y, RGB(255, 0, 0));
	}
}