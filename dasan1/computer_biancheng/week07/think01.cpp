#include <Windows.h>
#pragma comment(lib, "msimg32.lib")////
#include <iostream>
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG Msg;
	WNDCLASS wndclass;
	TCHAR lpszTitle[] = L"���������";

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
		MessageBox(NULL, L"ע�ᴰ��ʧ��", L"ע�ᴰ��ʧ��", MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(L"xiang", lpszTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	if (!hwnd)
	{
		MessageBox(NULL, L"��������ʧ��", L"��������ʧ��", MB_ICONERROR);
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
	HDC hdc, hdcMem;
	PAINTSTRUCT ps;
	HBITMAP hBitmap;
	BITMAP bm;
	TCHAR str[20] = L"I am a monster��";
	int len = lstrlen(str);
	RECT rect;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hdcMem = CreateCompatibleDC(hdc);
		hBitmap = (HBITMAP)LoadImage(NULL, L"Monster.bmp", IMAGE_BITMAP,
			0, 0, LR_LOADFROMFILE);
		SelectObject(hdcMem, hBitmap);

		GetObject(hBitmap, sizeof(BITMAP), &bm);
		SetBkMode(hdcMem, TRANSPARENT);
		rect = { 0, 0, bm.bmWidth, bm.bmHeight };
		DrawText(hdcMem, str, -1, &rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

		BitBlt(hdc, 30, 50, bm.bmWidth, bm.bmHeight, hdcMem,
			0, 0, SRCCOPY); // ��ʼ��ʽ

		BitBlt(hdc, 200, 50, bm.bmWidth, bm.bmHeight, hdcMem,
			0, 0, SRCCOPY); // λ�øı�

		SetStretchBltMode(hdc, COLORONCOLOR);
		StretchBlt(hdc, 400, 50, bm.bmWidth * 2, bm.bmHeight * 2, hdcMem,
			0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY); // ������Ŵ�����

		StretchBlt(hdc, 30, 250, bm.bmWidth / 2, bm.bmHeight / 2, hdcMem,
			0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY); // �������С����

		DeleteDC(hdcMem);
		DeleteObject(hBitmap);
		EndPaint(hwnd, &ps);
		return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}