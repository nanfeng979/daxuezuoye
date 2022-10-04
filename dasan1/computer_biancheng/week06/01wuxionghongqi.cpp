#include <Windows.h>
#define WINDOW_WIDTH 950
#define WINDOW_HEIGHT 650

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
		CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT,
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
PAINTSTRUCT ps;//
HBRUSH hBrush1, hOldBrush;//
HPEN hOldPen; // 初始时的画笔样式
HPEN hPen1 = CreatePen(PS_NULL, 0, RGB(0, 0, 0)); // 画笔样式为：空线

#include <cmath>////
#define PI 3.14159265358979323846////
int nWidth = 900 / 2 / 15;
int nHeight = 600 / 2 / 10;
void SetFivePoints(POINT* pts, int nCount, int r, int angle, POINT pOrg);////
void DrawFiveStart(HDC hdc);////
void DrawSmallFiveStart(HDC hdc, int angle, POINT ptOrg);////

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
		DeleteObject(hBrush1); // 删除笔刷样式hBrush1

		SelectObject(hdc, hOldPen); // 恢复初始时的画笔样式
		SelectObject(hdc, hOldBrush); // 恢复初始时的笔刷样式

		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

VOID PAINT(HWND hwnd, HDC hdc)
{
	hBrush1 = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));//
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush1);//

	// 红色背景
	Rectangle(hdc, 0, 0, 900, 600);//

	// 画出五角星
	hBrush1 = (HBRUSH)CreateSolidBrush(RGB(250, 244, 8));//
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush1);//

	hOldPen = (HPEN)SelectObject(hdc, hPen1);////
	DrawFiveStart(hdc);////

	// 画出小的五角星
	DrawSmallFiveStart(hdc, 70, { nWidth * 10, nHeight * 2 });////
	DrawSmallFiveStart(hdc, 120, { nWidth * 12, nHeight * 4 });////
	DrawSmallFiveStart(hdc, 90, { nWidth * 12, nHeight * 7 });////
	DrawSmallFiveStart(hdc, 70, { nWidth * 10, nHeight * 9 });////
}

void SetFivePoints(POINT* pts, int nCount, int r, int angle, POINT pOrg)////
{
	for (int i = 0; i < nCount; i++)////
	{
		pts[i].x = pOrg.x + (LONG)(r * cos((angle + i * 72) * PI / 180));////
		pts[i].y = pOrg.y - (LONG)(r * sin((angle + i * 72) * PI / 180));////
	}
}

void DrawFiveStart(HDC hdc)
{
	// 画出五角星
	POINT pts[5] = { 0 };////
	POINT pOrg = { 0 };////
	pOrg.x = 5 * nWidth;////
	pOrg.y = 5 * nHeight;////

	SetPolyFillMode(hdc, WINDING);
	SetFivePoints(pts, 5, 35 * 3, 90, pOrg);////
	POINT pNewPts[5] = { pts[0], pts[2], pts[4], pts[1], pts[3] };////
	Polygon(hdc, pNewPts, 5);////
}

void DrawSmallFiveStart(HDC hdc, int angle, POINT ptOrg)////
{
	POINT pts[5] = { 0 };////
	SetFivePoints(pts, 5, nHeight, angle, ptOrg);////
	POINT pNewPts[5] = { pts[0], pts[2], pts[4], pts[1], pts[3] };////
	Polygon(hdc, pNewPts, 5);////
}
