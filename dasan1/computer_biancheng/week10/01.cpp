#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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
	static HDC hdc;
	static PAINTSTRUCT ps;
	static RECT rt;
	static HBRUSH hBrush_red, hBrush_while, hOldBrush;

	static bool one = false, two = false;
	int x_pos, y_pos;

	switch (message)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rt);
		hBrush_red = CreateSolidBrush(RGB(255, 0, 0));
		hBrush_while = CreateSolidBrush(RGB(255, 255, 255));

		break;
	case WM_LBUTTONDOWN:
		x_pos = LOWORD(lParam);
		y_pos = HIWORD(lParam);

		if (x_pos >= 100 && x_pos <= 200 && y_pos >= 100 && y_pos <= 200)
		{
			one = !one;
		}
		else if (x_pos >= 400 && x_pos <= 500 && y_pos >= 100 && y_pos <= 400) {
			two = !two;
		}
		else {
			one = false;
			two = false;
		}
		
		InvalidateRect(hwnd, &rt, true);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		if (one)
		{
			hOldBrush = (HBRUSH)SelectObject(hdc, hBrush_red);
		}
		else {
			hOldBrush = (HBRUSH)SelectObject(hdc, hBrush_while);
		}
		Rectangle(hdc, 100, 100, 200, 200);

		if (two)
		{
			SelectObject(hdc, hBrush_red);
		}
		else {
			SelectObject(hdc, hBrush_while);
		}
		Rectangle(hdc, 400, 100, 500, 400);

		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		SelectObject(hdc, hOldBrush);
		DeleteObject(hBrush_red);
		DeleteObject(hBrush_while);

		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}