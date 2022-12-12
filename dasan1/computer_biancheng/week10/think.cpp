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
	static RECT rt, sm_rt;
	static float rect_x = 50, rect_y = 50; // 可移动的矩形的位置
	float pos_x, pos_y; // 鼠标位置
	static float diff_x, diff_y; // 鼠标的偏移量
	static bool rect_can_move = false, rect_in_RECT = false; // 


	switch (message)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rt);
		break;

	case WM_MOUSEMOVE:
		if (!(wParam & MK_LBUTTON))
			return 0;

		pos_x = LOWORD(lParam);
		pos_y = HIWORD(lParam);

		// 如果小矩形允许移动且不在大矩形内
		if (rect_can_move && !rect_in_RECT)
		{
			rect_x = pos_x - diff_x;
			rect_y = pos_y - diff_y;
		}

		InvalidateRect(hwnd, &rt, true);
		break;
	case WM_LBUTTONDOWN:

		pos_x = LOWORD(lParam);
		pos_y = HIWORD(lParam);

		// 如果鼠标在可移动矩形内
		if (pos_x >= 50 && pos_x <= 100 && pos_y >= 50 && pos_y <= 100)
		{
			// 获取偏移量
			diff_x = pos_x - 50;
			diff_y = pos_y - 50;
			rect_can_move = true;
		}

		break;
	case WM_LBUTTONUP:
		rect_can_move = false;

		// 当可移动矩形在大矩形之外时
		if (rect_x < 200 || rect_x > 400 - 50 || rect_y < 200 || rect_y > 400 - 50)
		{
			rect_x = 50;
			rect_y = 50;
		}
		else {
			rect_in_RECT = true;
		}
		InvalidateRect(hwnd, &rt, true);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		// 大矩形
		Rectangle(hdc, 200, 200, 400, 400);

		// 小矩形
		Rectangle(hdc, rect_x, rect_y, rect_x + 50, rect_y + 50);

		if (rect_in_RECT)
		{
			sm_rt.left = rect_x;
			sm_rt.top = rect_y;
			sm_rt.right = rect_x + 50;
			sm_rt.bottom = rect_y + 50;
			FillRect(hdc, &sm_rt, (HBRUSH)CreateSolidBrush(RGB(255, 0, 0)));
		}

		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}