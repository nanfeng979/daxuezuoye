#include <Windows.h>
#include <cmath>

#define windows_width 900
#define windows_height 600

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
VOID PAINT(HWND hwnd, HDC hdc);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG Msg;
	WNDCLASS wndclass;
	TCHAR lpszTitle[] = L"余庆祥设计";
	RECT wr = { 0, 0, windows_width, windows_height };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

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
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
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

HDC hdc;
HBRUSH hOldBrush; // 初始时的笔刷样式
HBRUSH hBrush1 = CreateSolidBrush(RGB(255, 0, 0)); // 笔刷样式为：红色实心笔刷
HFONT hOldFont; // 初始时的文字样式
HFONT hFont1 = CreateFont(30, 15, 0, 0,
	1300, 0, 0, 0, 0,
	0, 0, 10, 0, L"黑体"); // 文字样式为：30号黑体
static TCHAR str1[] = L"祝我们亲爱的祖国";
static TCHAR str2[] = L"生日快乐！";

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
		DeleteObject(hBrush1); // 删除笔刷样式hBrush1
		DeleteObject(hFont1); // 删除文字样式hFont1

		SelectObject(hdc, hOldBrush); // 恢复初始时的笔刷样式
		SelectObject(hdc, hOldFont); // 恢复初始时的文字样式

		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}


VOID PAINT(HWND hwnd, HDC hdc)
{
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush1);
	hOldFont = (HFONT)SelectObject(hdc, hFont1);

	Rectangle(hdc, 0, 0, windows_width, windows_height); // 绘制整个客户区的尺寸的矩形

	SetBkMode(hdc, TRANSPARENT); // 设置文字背景为透明模式
	SetTextColor(hdc, RGB(255, 255, 0)); // 设置字体颜色

	SetGraphicsMode(hdc, GM_ADVANCED); // 设置允许世界转换的高级图形模式。
	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm); // 使用当前所选字体的指标填充指定的缓冲区
	int text_spacing = tm.tmExternalLeading + tm.tmHeight; // 两行字体之间的间距
	// 分别移动间距使上下两行不拥挤
	RECT rect1 = { 0, 0, windows_width, windows_height - text_spacing };
	RECT rect2 = { 0, 0, windows_width, windows_height + text_spacing };

	// 两组文字分别根据位置信息，并垂直居中文本、使文本对齐到矩形底部、在矩形中水平居中居中文本
	DrawText(hdc, str1, -1, &rect1, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
	DrawText(hdc, str2, -1, &rect2, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
}