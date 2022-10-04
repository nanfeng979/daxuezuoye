#include <Windows.h>

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

#define diameter 200 // 对象直径
#define radius diameter / 2 // 对象半径
#define init_x 50 // 对象初始的x轴位置
#define init_y 50 // 对象初始的y轴位置
#define width init_x + diameter // 对象宽度
#define height init_y + diameter // 对象长度
#define spacing_x 16 // 对象之间的x轴间距
#define line_width 8 // 画笔样式的宽度
HDC hdc;
HPEN hOldPen; // 初始时的画笔样式
HPEN hPen1 = CreatePen(PS_SOLID, line_width, RGB(0, 0, 255)); // 画笔样式为：实线6宽度蓝色
HPEN hPen2 = CreatePen(PS_SOLID, line_width, RGB(0, 0, 0)); // 画笔样式为：实线6宽度黑色
HPEN hPen3 = CreatePen(PS_SOLID, line_width, RGB(255, 0, 0)); // 画笔样式为：实线6宽度红色
HPEN hPen4 = CreatePen(PS_SOLID, line_width, RGB(255, 255, 0)); // 画笔样式为：实线6宽度黄色
HPEN hPen5 = CreatePen(PS_SOLID, line_width, RGB(0, 255, 0)); // 画笔样式为：实线6宽度绿色

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
		hdc = GetDC(hwnd); // 获取设备环境
		PAINT(hwnd, hdc); // 绘制
		ReleaseDC(hwnd, hdc); // 释放设备环境
		break;
	case WM_DESTROY:
		DeleteObject(hPen1); // 删除画笔样式hPen1
		DeleteObject(hPen2); // 删除画笔样式hPen2
		DeleteObject(hPen3); // 删除画笔样式hPen3
		DeleteObject(hPen4); // 删除画笔样式hPen4
		DeleteObject(hPen5); // 删除画笔样式hPen5

		SelectObject(hdc, hOldPen); // 恢复初始时的画笔样式

		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

VOID PAINT(HWND hwnd, HDC hdc)
{
	hOldPen = (HPEN)SelectObject(hdc, hPen1); // 保存初始时的画笔样式，并设置画笔为hPen1样式
	Arc(hdc, init_x, init_y,
		width, height, 0, 0, 0, 0); // 绘制圆弧

	SelectObject(hdc, hPen2); // 设置画笔为hPen2样式
	Arc(hdc, init_x + diameter * 1 + spacing_x * 1, init_y,
		width + diameter * 1 + spacing_x * 1, height, 0, 0, 0, 0); // 绘制圆弧

	SelectObject(hdc, hPen3); // 设置画笔为hPen3样式
	Arc(hdc, init_x + diameter * 2 + spacing_x * 2, init_y,
		width + diameter * 2 + spacing_x * 2, height, 0, 0, 0, 0); // 绘制圆弧

	SelectObject(hdc, hPen4); // 设置画笔为hPen4样式
	Arc(hdc, init_x + radius, init_y + radius,
		width + radius, height + radius, 0, 0, 0, 0); // 绘制圆弧

	SelectObject(hdc, hPen5); // 设置画笔为hPen5样式
	Arc(hdc, init_x + radius + diameter * 1 + spacing_x * 1, init_y + radius,
		width + radius + diameter * 1 + spacing_x * 1, height + radius, 0, 0, 0, 0); // 绘制圆弧
}