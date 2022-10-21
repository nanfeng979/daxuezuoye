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
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH hBrush1, hBrush2, hOldBrush;
	hdc = BeginPaint(hwnd, &ps);
	hBrush1 = CreateSolidBrush(RGB(0, 255, 0));
	hBrush2 = CreateSolidBrush(RGB(255, 0, 0));
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush1);

	static float mul = 1.0;
	float base_width = 200.0;
	float step = 0.01;

	switch (message)
	{
	case WM_CREATE:
		SetTimer(hwnd, 1, 50, NULL);
		return 0;
	case WM_PAINT:
		
		SelectObject(hdc, hBrush1);
		Rectangle(hdc, 50, 50, base_width + 50, 20 + 50);
		SelectObject(hdc, hBrush2);
		Rectangle(hdc, 50, 50, base_width * mul + 50, 20 + 50);

		break;
	case WM_TIMER:
		if (mul > 0)
		{
			mul -= step;
		}
		else {
			mul = 0; // 有时会遇到不可预期的情况：mul < 0;
		}
		InvalidateRect(hwnd, NULL, true);
		return 0;
	case WM_DESTROY:
		SelectObject(hdc, hOldBrush);
		DeleteObject(hBrush1);
		KillTimer(hwnd, 1);
		EndPaint(hwnd, &ps);
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}