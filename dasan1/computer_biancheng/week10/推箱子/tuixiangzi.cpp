#include <Windows.h>
#include <cstdlib>
#include <time.h>


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
	static HDC hdc, hdcMem;
	static PAINTSTRUCT ps;
	static RECT rt, sm_rt, lankuang_rt;
	static HBRUSH hBrush;
	static HPEN hPen_red, hPen_blue;
	static HBITMAP hBitmap;
	static BITMAP bm;
	static bool can_init = true; // 定义"允许初始化"变量
	static UINT map_arr[20][10]; // 存储全局坐标数据
	static UINT lankuang_arr[4][2]; // 存储自身坐标数据
	static int  box_arr[4][2]; // 存储自身坐标数据
	static UINT box_checked = 5; // 被选中的箱子
	int pos_x, pos_y; // 鼠标的"世界"坐标位置
	static bool box_is_arrived[4] = {false, false, false, false}; // 定义"箱子"是否已经到达位置

	switch (message)
	{
	case WM_CREATE:
		ShowWindow(hwnd, SW_MAXIMIZE);
		GetClientRect(hwnd, &rt);
		break;

	case WM_LBUTTONDOWN:
		if (!(wParam & VK_LBUTTON))
			return 0;
		pos_x = LOWORD(lParam);
		pos_y = HIWORD(lParam);
		
		for (int i = 0; i < 4; i++)
		{
			if (pos_x >= box_arr[i][0] * 50 + 200 + 1 && pos_x <= box_arr[i][0] * 50 + 200 + 1 + 50 &&
				pos_y >= box_arr[i][1] * 50 + 100 + 1 && pos_y <= box_arr[i][1] * 50 + 100 + 1 + 50)
				box_checked = i;
		}

		InvalidateRect(hwnd, &rt, true);
		break;

	case WM_KEYDOWN:
		// 箱子进入到边框后就终止判断
		if (box_is_arrived[box_checked])
			break;

		for (int i = 0; i < 4; i++)
		{
			if (box_arr[box_checked][0] - 1 == box_arr[i][0] && box_arr[box_checked][1] - 1 == box_arr[i][1] &&
				box_arr[box_checked][0] + 1 == box_arr[i][0] && box_arr[box_checked][0] - 1 == box_arr[i][0])
			{
				return 0;
			}
		}
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case VK_LEFT:
			// 箱子向左移动
			if (box_arr[box_checked][0] - 1 < 0)
				return 0;
			// 箱子与箱子之间的碰撞
			for (int i = 0; i < 4; i++)
			{
				if (box_checked == i) continue;
				if (box_arr[box_checked][0] - 1 == box_arr[i][0] && box_arr[box_checked][1] == box_arr[i][1])
				{
					return 0;
				}
			}
			box_arr[box_checked][0] -= 1;
			break;
		case VK_UP:
			// 箱子向上移动
			if (box_arr[box_checked][1] - 1 < 0)
				return 0;
			for (int i = 0; i < 4; i++)
			{
				if (box_checked == i) continue;
				if (box_arr[box_checked][1] - 1 == box_arr[i][1] && box_arr[box_checked][0] == box_arr[i][0])
				{
					return 0;
				}
			}
			box_arr[box_checked][1] -= 1;
			break;
		case VK_RIGHT:
			// 箱子向右移动
			if (box_arr[box_checked][0] + 1 > 20 - 1)
				return 0;
			for (int i = 0; i < 4; i++)
			{
				if (box_checked == i) continue;
				if (box_arr[box_checked][0] + 1 == box_arr[i][0] && box_arr[box_checked][1] == box_arr[i][1])
				{
					return 0;
				}
			}
			box_arr[box_checked][0] += 1;
			break;
		case VK_DOWN:
			// 箱子向下移动
			if (box_arr[box_checked][1] + 1 > 10 - 1)
				return 0;
			for (int i = 0; i < 4; i++)
			{
				if (box_checked == i) continue;
				if (box_arr[box_checked][1] + 1 == box_arr[i][1] && box_arr[box_checked][0] == box_arr[i][0])
				{
					return 0;
				}
			}
			box_arr[box_checked][1] += 1;
			break;
		}

		InvalidateRect(hwnd, &rt, true);
		break;

	case WM_PAINT:
		FillRect(hdc, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH));

		// 初始化
		hdc = BeginPaint(hwnd, &ps);
		hPen_blue = CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
		hPen_red = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
		hdcMem = CreateCompatibleDC(hdc);
		hBitmap = (HBITMAP)LoadImage(NULL, L"box.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		SelectObject(hdcMem, hBitmap);
		GetObject(hBitmap, sizeof(BITMAP), &bm);


		// 画横线
		for (int i = 0; i < 21; i++)
		{
			MoveToEx(hdc, i * 50 + 200, 0 + 100, NULL);
			LineTo(hdc, i * 50 + 200, 500 + 100);
		}
		// 画竖线
		for (int j = 0; j < 11; j++)
		{
			MoveToEx(hdc, 0 + 200, j * 50 + 100, NULL);
			LineTo(hdc, 1000 + 200, j * 50 + 100);
		}


		// 初始化 --只执行一次
		if (can_init)
		{
			// 初始化数据
			// 0: 空白, 1: 蓝框, 2: 箱子
			for (int i = 0; i < 20; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					map_arr[i][j] = 0;
				}
			}

			// 随机生成4个箱子的位置
			for (int i = 0; i < 4;)
			{
				int map_x = (rand() * time(0) % 20);
				int map_y = (rand() * time(0) % 10);
				if (map_arr[map_x][map_y] == 0)
				{
					// 将蓝框位置数据放到box_arr里
					lankuang_arr[i][0] = map_x;
					lankuang_arr[i][1] = map_y;

					map_arr[map_x][map_y] = 1;
					i++;
				}
			}

			// 随机生成4个箱子的位置
			for (int i = 0; i < 4;)
			{
				int map_x = (rand() * time(0) % 20);
				int map_y = (rand() * time(0) % 10);
				if (map_arr[map_x][map_y] == 0)
				{
					// 将箱子位置数据放到box_arr里
					box_arr[i][0] = map_x;
					box_arr[i][1] = map_y;

					map_arr[map_x][map_y] = 2;
					i++;
				}
			}

			// 禁止初始化
			can_init = false;
		}


		// 输出边框
		for (int i = 0; i < 4; i++)
		{
			SelectObject(hdc, hPen_blue);

			//输出蓝框
			for (int j = 0; j < 4; j++)
			{
				// 如果箱子和蓝框重叠时则输出红框
				if (lankuang_arr[i][0] == box_arr[j][0] && lankuang_arr[i][1] == box_arr[j][1])
				{
					SelectObject(hdc, hPen_red);
					box_is_arrived[j] = true;
					break;
				}
			}

			int lankuang_x = lankuang_arr[i][0];
			int lankuang_y = lankuang_arr[i][1];
			lankuang_rt.left = lankuang_x * 50 + 200 + 1;
			lankuang_rt.top = lankuang_y * 50 + 100 + 1;
			lankuang_rt.right = lankuang_rt.left + 50;
			lankuang_rt.bottom = lankuang_rt.top + 50;

			Rectangle(hdc, lankuang_rt.left, lankuang_rt.top, lankuang_rt.right, lankuang_rt.bottom);
		}

		// 输出箱子
		for (int i = 0; i < 4; i++)
		{
			int box_x = box_arr[i][0];
			int box_y = box_arr[i][1];
			
			BitBlt(hdc, box_x * 50 + 200 + 1, box_y * 50 + 100 + 1, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
		}
		

		// 如果四个都重叠了，则显示胜利文字
		if (box_is_arrived[0] && box_is_arrived[1] && box_is_arrived[2] && box_is_arrived[3])
		{
			TextOut(hdc, 0, 0, L"WELL DONE!!", lstrlen(L"WELL DONE!!"));
		}

		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		DeleteDC(hdcMem);
		DeleteObject(hPen_blue);
		DeleteObject(hPen_red);
		DeleteObject(hBitmap);
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}