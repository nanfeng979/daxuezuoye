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
	static RECT rt, rtDraw;
	static bool shift_down = false;

	switch (message)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rt);

		break;
	case WM_MOUSEMOVE:
		if (!(wParam & MK_LBUTTON))
			return 0;

		rtDraw.right = LOWORD(lParam);
		rtDraw.bottom = HIWORD(lParam);

		InvalidateRect(hwnd, &rt, true);
		break;
	case WM_LBUTTONDOWN:
		rtDraw.left = LOWORD(lParam);
		rtDraw.top = HIWORD(lParam);

		shift_down = false;
		if (GetKeyState(VK_SHIFT) & 0x8000)
		{
			shift_down = true;

		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		if (shift_down)
		{
			Ellipse(hdc, rtDraw.left, rtDraw.top, rtDraw.right, rtDraw.bottom);
		}
		else {
			Rectangle(hdc, rtDraw.left, rtDraw.top, rtDraw.right, rtDraw.bottom);
		}

		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}