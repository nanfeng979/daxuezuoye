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
	wndclass.hbrBackground = NULL;
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
	HDC hdc, hdcMem;
	PAINTSTRUCT ps;
	hdc = BeginPaint(hwnd, &ps);
	hdcMem = CreateCompatibleDC(hdc);
	RECT rt;
	GetClientRect(hwnd, &rt);
	HBITMAP hBitmap;
	hBitmap = CreateCompatibleBitmap(hdc, rt.right - rt.left, rt.bottom - rt.top);
	SelectObject(hdcMem, hBitmap);

	static int x = 0, y = 0;
	int p = 70; // 确定一个焦点位置
	static int step = 20;

	switch (message)
	{
	case WM_CREATE:
		SetTimer(hwnd, 1, 100, NULL);
		return 0;
	case WM_PAINT:
		FillRect(hdcMem, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH));

		for (int x = 0, y = 0; x < 250 || y < rt.bottom; x++)
		{
			y = x * x / (2 * p);
			if (x % step == 0) {
				Ellipse(hdcMem, x - 25, y - 25, x + 25, y + 25);
				Arc(hdcMem, x - 55, y - 25, x - 5, y + 25, x - 5, y + 25, x - 15, y - 25);
				Arc(hdcMem, x + 5, y - 25, x + 55, y + 25, x + 15, y - 25, x + 20, y + 25);
			}

			SetPixel(hdcMem, x, y, RGB(255, 0, 0));
		}

		BitBlt(hdc, 0, 0, rt.right, rt.bottom, hdcMem, 0, 0, SRCCOPY);
		break;
	case WM_TIMER:
		step++;
		if (step > 25) step = 20;
		InvalidateRect(hwnd, NULL, true);
		return 0;
	case WM_DESTROY:
		KillTimer(hwnd, 1);
		DeleteObject(hBitmap);
		DeleteDC(hdcMem);
		EndPaint(hwnd, &ps);
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}